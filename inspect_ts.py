from tree_sitter import Language, Parser
import tree_sitter_cpp as tscpp

CPP_LANGUAGE = Language(tscpp.language())
parser = Parser(CPP_LANGUAGE)
query = CPP_LANGUAGE.query("(function_definition) @func")

print(dir(query))
