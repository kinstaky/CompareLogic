#ifndef __ARITHMETIC_GRAMMAR_H__
#define __ARITHMETIC_GRAMMAR_H__

#include <vector>

#include "parser/production.h"
#include "parser/token.h"
#include "parser/grammar.h"


/**
 * This class represents a arithmetic grammar only includes the operation
 * addition '+' and multiplication '*'.
 * 
 */
class AddMultiGrammar final : public Grammar<double> {
public:
	
	/// @brief constructor
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	AddMultiGrammar() noexcept;


	/// @brief destructor
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	virtual ~AddMultiGrammar() noexcept;

private:
	std::vector<Symbol*> symbols_;
};



/**
 * This class represents a arithmetic grammar includes the operation
 * addition '+', subtraction '-', multiplication '*', and division '/'.
 * 
 */
class ArithmeticGrammar final : public Grammar<double> {
public:

	/// @brief constructor
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	ArithmeticGrammar() noexcept;

	/// @brief destructor
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	virtual ~ArithmeticGrammar() noexcept;

private:
	std::vector<Symbol*> symbols_;
};


#endif /* __ARITHMETIC_GRAMMAR_H__ */