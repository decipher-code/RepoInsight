import os
os.environ["TRANSFORMERS_NO_AD_HOC_PARSING"] = "1"
import logging
logging.getLogger("transformers").setLevel(logging.ERROR)
import os
os.environ["TOKENIZERS_PARALLELISM"] = "false"
import networkx as nx
import chromadb
from typing import TypedDict, Annotated, List, Union
from langchain_core.tools import tool
from langchain_core.messages import BaseMessage, HumanMessage, AIMessage, SystemMessage, ToolMessage
from langgraph.graph import StateGraph, END
import operator


client = chromadb.PersistentClient(path="./repo_db")
collection = client.get_collection(name="music_player_repo")
try:
    G = nx.read_gml("repo_graph.gml")
    print(f"Loaded graph with {len(G.nodes)} nodes.")
except:
    G = nx.DiGraph()


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


from langchain_groq import ChatGroq

llm = ChatGroq(
    model="llama-3.1-8b-instant",
    api_key=os.environ.get("GROQ_API_KEY"),
)

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

    prompt = "You are a C++ expert. Give 1-sentence answers. Use tools only if essential."
    
    
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
