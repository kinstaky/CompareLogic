set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

doxygen_add_docs(
	docs 	

	parser/token.h
	parser/lexer.h
	parser/production.h
	parser/grammar.h
	parser/syntax_parser.h
	arithmetic_grammar.h
	logical_grammar.h
	logic_comparer.h

	"${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"

	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
)
