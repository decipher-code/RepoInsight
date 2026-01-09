import os
import chromadb
from tree_sitter import Language, Parser
import tree_sitter_cpp as tscpp
import networkx as nx

# Initializing the C++ Parser
from tree_sitter import Query
CPP_LANGUAGE = Language(tscpp.language())
parser = Parser(CPP_LANGUAGE)

#  Initializing Vector DB and Graph
client = chromadb.PersistentClient(path="./repo_db")
collection = client.get_or_create_collection(name="music_player_repo")
G = nx.DiGraph()

def extract_cpp_symbols(file_path):
    with open(file_path, "rb") as f:
        code = f.read()
    tree = parser.parse(code)
    
    # Query for Classes, Functions, and Includes (Cross-file mapping)
    query = Query(CPP_LANGUAGE, """
        (function_definition (function_declarator) @func_name)
        (class_specifier (type_identifier) @class_name)
        (preproc_include (string_literal) @include_path)
    """)
    
    # Secondary query to find function calls inside a function body
    call_query = Query(CPP_LANGUAGE, """
        (call_expression function: (identifier) @callee)
    """)
    
    captures = query.captures(tree.root_node)
    chunks = []
    
    for node, tag in captures:
        # Building Vector DB chunks
        chunks.append({
            "id": f"{file_path}_{node.start_byte}",
            "text": node.parent.text.decode('utf8'),
            "metadata": {"file": file_path, "type": tag, "name": node.text.decode('utf8')}
        })

        # Building Graph Edges (Function Calls)
        if tag == "func_name":
            caller_name = node.text.decode('utf8')
            # Look for calls inside this function's body 
            function_body = node.parent
            calls = call_query.captures(function_body)
            for call_node, _ in calls:
                callee_name = call_node.text.decode('utf8')
                G.add_edge(caller_name, callee_name)
                
    return chunks

#  Processing data
repo_path = "./my_music_player" 
for root, _, files in os.walk(repo_path):
    for file in files:
        if file.endswith((".cpp", ".h")):
            path = os.path.join(root, file)
            data = extract_cpp_symbols(path)
            for item in data:
                collection.add(
                    ids=[item["id"]],
                    documents=[item["text"]],
                    metadatas=[item["metadata"]]
                )
#  Saving the Graph
print(f"Graph nodes: {len(G.nodes)}")
print(f"Graph edges: {len(G.edges)}")
nx.write_gml(G, "repo_graph.gml")

print("Saved dependency graph to repo_graph.gml")
