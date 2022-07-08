/*
 * This file defines the logic grammar class.
 */

#ifndef __LOGICAL_GRAMMAR_H__
#define __LOGICAL_GRAMMAR_H__

#include <string>
#include <vector>

#include "parser/grammar.h"

/**
 * This class represents a logical grammar that only includes operations
 * and '&' and or '|'.
 * 
 */
class LogicalGrammar final : public Grammar<bool> {
public:

	/// @brief constructor
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	LogicalGrammar() noexcept;



	/// @brief destructor
	///
	/// @exceptsafe Shall not throw exceptions.
	///
	virtual ~LogicalGrammar() noexcept;


private:
	std::vector<Symbol*> symbols_;
};



#endif /* __LOGIC_GRAMMAR_H__ */