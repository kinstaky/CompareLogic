# Compare logical expressions
add_executable(
	compare
	compare_logical_expression.cpp
)
target_compile_features(
	compare
	PRIVATE cxx_std_17
)
target_link_libraries(
	compare
	PRIVATE logical_grammar
	PRIVATE lexer
	PRIVATE syntax_parser
	PRIVATE logic_comparer
)
