#include "parser/lexer.h"

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "parser/token.h"



// error inputs
const std::string kErrorInputExpression[] = {
	"0ac",				// ERROR: variable start with digit
	"abc & 0",			// ERROR: variable start with digit
	"#abc",				// ERROR: varaible start with invalid character '#'
	"abc & @d"			// ERROR: variable start with invalid character '@'
};



// appropriate inputs
const std::string kInputExpression[] = {
	"A",
	"A_",
	"A0",
	"aA0_",
	"A | B",
	"A0 & Bb",
	"(Aa0_)",
	"A | B & ( B | C)",
	"A|B&(B|C)",
	"(a&b)|(c&d)"
};



const std::vector<std::string> kOutputValue[] = {
	{"A"},
	{"A_"},
	{"A0"},
	{"aA0_"},
	{"A", "|", "B"},
	{"A0", "&", "Bb"},
	{"(", "Aa0_", ")"},
	{"A", "|", "B", "&", "(", "B", "|", "C", ")"},
	{"A", "|", "B", "&", "(", "B", "|", "C", ")"},
	{"(", "a", "&", "b", ")", "|", "(", "c", "&", "d", ")"}
};

const std::vector<int> kOutputType[] = {
	{kSymbolType_Identifier},
	{kSymbolType_Identifier},
	{kSymbolType_Identifier},
	{kSymbolType_Identifier},
	{kSymbolType_Identifier, kSymbolType_Operator, kSymbolType_Identifier},
	{kSymbolType_Identifier, kSymbolType_Operator, kSymbolType_Identifier},
	{kSymbolType_Operator, kSymbolType_Identifier, kSymbolType_Operator},
	{
		kSymbolType_Identifier, kSymbolType_Operator, kSymbolType_Identifier,
		kSymbolType_Operator, kSymbolType_Operator, kSymbolType_Identifier,
		kSymbolType_Operator, kSymbolType_Identifier, kSymbolType_Operator
	},
	{
		kSymbolType_Identifier, kSymbolType_Operator, kSymbolType_Identifier,
		kSymbolType_Operator, kSymbolType_Operator, kSymbolType_Identifier,
		kSymbolType_Operator, kSymbolType_Identifier, kSymbolType_Operator
	},
	{
		kSymbolType_Operator, kSymbolType_Identifier, kSymbolType_Operator,
		kSymbolType_Identifier, kSymbolType_Operator, kSymbolType_Operator,
		kSymbolType_Operator, kSymbolType_Identifier, kSymbolType_Operator,
		kSymbolType_Identifier, kSymbolType_Operator
	}
};



TEST(LexerTest, HandleErrorInput) {
	Lexer lexer;
	int index = 0;
	for (const std::string &expr : kErrorInputExpression) {
		std::vector<TokenPtr> tokens;
		int result = lexer.Analyse(expr, tokens);
		
		EXPECT_EQ(result, -1)
			<< "Lexical parse cannot handle the input error: #" << index
			<< ", result " << result << ".";
		
		++index;
	}
}



TEST(LexerTest, Analyse) {
	Lexer lexer;
	int expression_index = 0;
	for (const std::string &expr : kInputExpression) {
		std::vector<TokenPtr> tokens;
		int result = lexer.Analyse(expr, tokens);

		// check return result
		ASSERT_EQ(result, 0)
			<< "Lexer recognize the correct input as wrong: #"
			<< expression_index << ", result " << result << ".";


		// check tokens size
		EXPECT_EQ(tokens.size(), kOutputValue[expression_index].size())
			<< "Lexer generate token size error: expression #"
			<< expression_index << ". Get tokens size " << tokens.size()
			<< " but need " << kOutputValue[expression_index].size() << ".";

		int index = 0;
		for (auto &t : tokens) {

			// chekc token value
			EXPECT_EQ(t->Value(), kOutputValue[expression_index][index])
				<< "Lexical parser generate token error: expression #"
				<< expression_index << "token #" << index
				<< ". Get token " << t->Value() << " but need "
				<< kOutputValue[expression_index][index] << ".";


			// check token type
			EXPECT_EQ(tokens[index]->Type(), kOutputType[expression_index][index])
				<< "Lexical parser generate token error: expression #"
				<< expression_index << "token #" << index
				<< ". Get token type " << t->Type() << " but need "
				<< kOutputType[expression_index][index] << ".";


			++index;
		}

		++expression_index;
	}
}