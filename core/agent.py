import os
os.environ["TRANSFORMERS_NO_AD_HOC_PARSING"] = "1"
import logging
logging.getLogger("transformers").setLevel(logging.ERROR)
import os
os.environ["TOKENIZERS_PARALLELISM"] = "false"
import networkx as nx
import chromadb
from typing import TypedDict, Annotated, List, Union
from langchain_openai import ChatOpenAI
from langchain_core.tools import tool
from langchain_core.messages import BaseMessage, HumanMessage, AIMessage, SystemMessage, ToolMessage
from langgraph.graph import StateGraph, END
import operator

# --- setup connections ---
client = chromadb.PersistentClient(path="./repo_db")
collection = client.get_collection(name="music_player_repo")
try:
    G = nx.read_gml("repo_graph.gml")
    print(f"Loaded graph with {len(G.nodes)} nodes.")
except:
    G = nx.DiGraph()

# --- tools ---
@tool
def code_search_tool(query: str):
    """Searches the C++ codebase for semantic logic."""
    print(f"DEBUG: Searching for {query}")
    results = collection.query(query_texts=[query], n_results=3)
    docs = results['documents'][0] if results['documents'] else []
    return "\n\n".join(docs) if docs else "No results found."

@tool
def dependency_trace_tool(symbol_name: str):
    """Finds dependencies of a symbol."""
    print(f"DEBUG: Tracing {symbol_name}")
    if G.has_node(symbol_name):
        return f"Symbol: {symbol_name}\nCalled by: {list(G.predecessors(symbol_name))}\nCalls: {list(G.successors(symbol_name))}"
    return f"Symbol '{symbol_name}' not found."

tools = [code_search_tool, dependency_trace_tool]
tool_map = {t.name: t for t in tools}


OPENROUTER_API_KEY = "sk-or-....."

if OPENROUTER_API_KEY == "sk-or-...":
    OPENROUTER_API_KEY = os.environ.get("OPENROUTER_API_KEY")

if not OPENROUTER_API_KEY:
    try:
        OPENROUTER_API_KEY = input("Please enter your OpenRouter API Key: ")
    except:
        pass

if not OPENROUTER_API_KEY:
    print("Error: No API Key provided. Please edit agent.py to set OPENROUTER_API_KEY.")
    exit(1)

# Configure Client for OpenRouter
# AVAILABLE FREE MODELS (Uncomment one if others fail):
# model="meta-llama/llama-3.1-8b-instruct:free"   # (Often busy/404)
# model="google/gemini-2.0-flash-exp:free"      # (Often rate limited)
# model="microsoft/phi-3-mini-128k-instruct:free" # (Good alternative)
# model="mistralai/mistral-7b-instruct:free"      # (Reliable fallback)

llm = ChatOpenAI(
    model="openrouter/auto", # Stable free endpoint
    openai_api_key=OPENROUTER_API_KEY,
    openai_api_base="https://openrouter.ai/api/v1",
    max_tokens=400,
    default_headers={
        "HTTP-Referer": "http://localhost:3000", # Required by OpenRouter
        "X-Title": "RepoInsight_Project",
    }
)
# llm = ChatOpenAI(
#     model="microsoft/phi-3-mini-128k-instruct:free", # Trying Phi-3 Mini which is fast and supports context
#     openai_api_key=OPENROUTER_API_KEY,
#     openai_api_base="https://openrouter.ai/api/v1",
#     default_headers={
#         "HTTP-Referer": "http://localhost:3000",
#         "X-Title": "RepoInsight Agent"
#     }
# )
llm_with_tools = llm.bind_tools(tools)

class AgentState(TypedDict):
    messages: Annotated[List[BaseMessage], operator.add]

def call_model(state):
    messages = state["messages"]
    response = llm_with_tools.invoke(messages)
    return {"messages": [response]}

def call_tools(state):
    last_message = state["messages"][-1]
    tool_calls = last_message.tool_calls
    results = []
    for t in tool_calls:
        print(f"Running tool: {t['name']}")
        tool_func = tool_map[t['name']]
        output = tool_func.invoke(t['args'])
        results.append(ToolMessage(tool_call_id=t['id'], name=t['name'], content=str(output)))
    return {"messages": results}

def should_continue(state):
    last_message = state["messages"][-1]
    if last_message.tool_calls:
        return "tools"
    return END

workflow = StateGraph(AgentState)
workflow.add_node("agent", call_model)
workflow.add_node("tools", call_tools)
workflow.set_entry_point("agent")
workflow.add_conditional_edges("agent", should_continue)
workflow.add_edge("tools", "agent")
app = workflow.compile()

if __name__ == "__main__":
    # prompt = """You are a Microsoft Principal Software Engineer. 
    # Your goal is to explain the architecture of a C++ Music Player repo.
    # Rules:
    # 1. Use code_search_tool to find implementations.
    # 2. Use dependency_trace_tool to see how files relates.
    # 3. Look for raw pointers and mention memory safety.
    # """
    prompt = """You are a Microsoft Principal Software Engineer. 
Your goal is to explain architecture briefly.
Rules:
1. Once you find the function name and the file it's in, STOP searching for the full code.
2. If you find a call chain like 'A calls B calls C', stop and summarize immediately.
3. Do not perform more than 10 searches total.
"""
   
    
    
    query = """
Analyze the interaction between main.cpp and the Song/Playlist classes:
1. Locate the Song object instantiation in main.cpp.
2. Identify the function in main.cpp or MusicPlayerApp that handles adding a song to a playlist.
3. Use dependency_trace_tool on that function to see which Playlist method it calls.
Provide a concise summary of the function call chain.
"""
    print(f"User: {query}")
    inputs = {"messages": [SystemMessage(content=prompt), HumanMessage(content=query)]}
    result = app.invoke(inputs,
        config={"recursion_limit": 50}
        )
    print("\nFINAL ANSWER:\n", result["messages"][-1].content)
