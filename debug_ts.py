from tree_sitter import Language, Parser, Query
import tree_sitter_cpp as tscpp

CPP_LANGUAGE = Language(tscpp.language())
parser = Parser(CPP_LANGUAGE)
source_code = b"void foo() {}"
tree = parser.parse(source_code)

query = Query(CPP_LANGUAGE, "(function_definition (function_declarator) @func_name)")

# Try matches
try:
    print("Testing matches():")
    matches = query.matches(tree.root_node)
    print(type(matches))
    for m in matches:
        print(m)
except Exception as e:
    print(f"matches failed: {e}")

# Try captures (just in case, but we know it failed)
try:
    print("Testing captures():")
    # captures = query.captures(tree.root_node) # We know this fails
    pass
except Exception:
    pass
