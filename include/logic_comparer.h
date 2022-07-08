#ifndef __LOGIC_COMPARER_H__
#define __LOGIC_COMPARER_H__

#include <vector>

#include "parser/lexer.h"
#include "parser/syntax_parser.h"
#include "logical_grammar.h"


class LogicComparer {
public:
	
	/// @brief constructor
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	LogicComparer() noexcept;



	/// @brief default destructor
	///
	~LogicComparer() = default;


	/// @brief compare two logical expression
	///
	/// @param[in] line1 first logical expression
	/// @param[in] line2 second logical expression
	/// @return true if equal, false not equal
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	bool Compare(const std::string &line1, const std::string &line2) noexcept;


private:

	// @brief compare identifiers from two logical expressions
	///
	/// @returns true if identical, false otherwise
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	bool CompareIdentifiers() noexcept;


	/// @brief compare value of two logical expressions
	///
	/// @returns true if identical, false otherwise
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	bool CompareValues() noexcept;



	/// @brief get the irrelevant identifiers
	///
	/// @param[in] index the index of the expression
	/// @param[out] identifiers the list of irrelevant identifiers
	/// @returns 0 on success, -1 on failure
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	int IrrelevantIdentifiers(int index, std::vector<Identifier*> &identifiers) noexcept;


	Lexer lexer_[2];
	LogicalGrammar grammar_[2];
	SLRSyntaxParser<bool> parser_[2];
	std::vector<bool> is_irrelevant_[2];
};



#endif