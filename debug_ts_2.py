import tree_sitter
from tree_sitter import Language, Parser, Query
import tree_sitter_cpp as tscpp
import pprint

print("Tree-sitter items:")
pprint.pprint(dir(tree_sitter))

CPP_LANGUAGE = Language(tscpp.language())
query = Query(CPP_LANGUAGE, "(function_definition) @func")

print("\nQuery object items:")
pprint.pprint(dir(query))
