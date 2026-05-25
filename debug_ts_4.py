from tree_sitter import Language, Parser, Query, QueryCursor
import tree_sitter_cpp as tscpp

CPP_LANGUAGE = Language(tscpp.language())
parser = Parser(CPP_LANGUAGE)
tree = parser.parse(b"void foo() {}")
query = Query(CPP_LANGUAGE, "(function_definition) @func")

cursor = QueryCursor()
print("Testing cursor.captures:")
captures = cursor.captures(query, tree.root_node)
# It's usually an iterator?
for capture in captures:
    print(capture)
    # Check what captures are
    # If it is (node, index), print query.capture_name_for_id(index)
    node, index = capture
    print(f"Node: {node.text}, Index: {index}")
    # print(f"Name: {query.capture_name_for_id(index)}") # Method might be different
