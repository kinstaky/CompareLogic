#include "logic_comparer.h"

#include <iostream>

LogicComparer::LogicComparer() noexcept
: parser_{grammar_, grammar_+1} {
}


bool LogicComparer::Compare(const std::string &line1, const std::string &line2) noexcept {
	std::string line[2] = {line1, line2};
	std::vector<TokenPtr> tokens[2];
	for (int i = 0; i < 2; ++i) {
		if (lexer_[i].Analyse(line[i], tokens[i]) < 0) {
			std::cerr << "Error: lexer analyse expression " << i << std::endl;
		}

		// // print token list for checking 
		// std::cout << "Token list " << i << std::endl;
		// for (auto token : tokens[i]) {
		// 	std::cout << "  " << token->Value() << std::endl;
		// }

		// parse the token list
		if (parser_[i].Parse(tokens[i]) < 0) {
			std::cerr << "Error: parser parse token list " << i << std::endl;
		}
	}
	return CompareIdentifiers() && CompareValues();
}


bool LogicComparer::CompareIdentifiers() noexcept {
	std::vector<Identifier*> id[2] = {parser_[0].IdentifierList(), parser_[1].IdentifierList()};
	std::vector<Identifier*> irrelevant_id[2];

	for (int i = 0; i < 2; ++i) {
		IrrelevantIdentifiers(i, irrelevant_id[i]);
	}
	
	// std::cout << "irrelevant identifiers size " << irrelevant_id[0].size() << "  " << irrelevant_id[1].size() << std::endl;

	if (id[0].size()-irrelevant_id[0].size() != id[1].size()-irrelevant_id[1].size()) {
		return false;
	}
	for (int i = 0; i < id[0].size(); ++i) {
		if (is_irrelevant_[0][i]) continue;

		bool match = false;
		for (int j = 0 ; j < id[1].size(); ++j) {
			if (is_irrelevant_[1][j]) continue;
			if (id[0][i]->Value() == id[1][j]->Value()) {
				match = true;
				break;
			}
		}
		if (!match) return false;
	}

	// std::cout << "identifiers are the same" << std::endl;
	return true;
}


bool LogicComparer::CompareValues() noexcept {
	std::vector<Identifier*> id[2] = {parser_[0].IdentifierList(), parser_[1].IdentifierList()};
	std::vector<Identifier*> irrelevant_id[2];
	for (int i = 0; i < 2; ++i) {
		IrrelevantIdentifiers(i, irrelevant_id[i]);
	}
	size_t size = id[0].size() - irrelevant_id[0].size();

	// initialize variables
	bool *variables = new bool[size];
	bool irrelevant_variable = 0;
	for (int i = 0; i < size; ++i) {
		variables[i] = 0;
	}
	// attach variables
	for (int i = 0; i < id[0].size(); ++i) {
		if (is_irrelevant_[0][i]) {
			// attach irrelevant variable to the first expression
			parser_[0].AttachIdentifier(id[0][i]->Value(), (void*)&irrelevant_variable);
		} else {
			parser_[0].AttachIdentifier(id[0][i]->Value(), (void*)(variables+i));
			parser_[1].AttachIdentifier(id[0][i]->Value(), (void*)(variables+i));
		}
	}
	// attach irrelevant variable to the second expression
	for (int i = 0; i < irrelevant_id[1].size(); ++i) {
		if (!is_irrelevant_[1][i]) continue;
		parser_[1].AttachIdentifier(id[1][i]->Value(), (void*)&irrelevant_variable);
	}


	while (true) {
		// check variables
		// for (int  i = 0; i < size; ++i) {
		// 	std::cout << variables[i] << "  ";
		// }
		// std::cout << std::endl;
		// std::cout << "value: " << parser_[0].Eval() << "  " << parser_[1].Eval() << std::endl;

		if (parser_[0].Eval() != parser_[1].Eval()) {
			std::cout << "Not equal!!!" << std::endl;
			delete[] variables;
			return false;
		}


		// change variables
		for (int i = 0; i < size; ++i) {
			if (variables[i] == 0) {
				variables[i] = 1;
				break;
			} else {
				variables[i] = 0;
			}
		}
		// check if is 0
		bool all_zero = true;
		for (int i = 0; i < size; ++i) {
			if (variables[i] == 1) {
				all_zero = false;
				break;
			}
		}
		if (all_zero) {
			break;
		}
	}

	delete[] variables;
	return true;
}



int LogicComparer::IrrelevantIdentifiers(int index, std::vector<Identifier*> &irrelevant_identifiers) noexcept {
	irrelevant_identifiers.clear();
	std::vector<Identifier*> id = parser_[index].IdentifierList();
	is_irrelevant_[index].resize(id.size());

	// attach variables
	bool *variables = new bool[id.size()];
	for (int i = 0; i < id.size(); ++i) {
		parser_[index].AttachIdentifier(i, (void*)(variables+i));
	}

	// loop for identifiers 
	for (int i = 0; i < id.size(); ++i) {
		// initialize variables
		for (int i = 0; i < id.size(); ++i) {
			variables[i] = 0;
		}
		
		bool not_change = true;					// whether the value of expression is changed when the specific identifier changes
		while (not_change) {
			bool eval1 = parser_[index].Eval();
			// change specific variable
			variables[i] = 1;
			bool eval2 = parser_[index].Eval();
			not_change = eval1 == eval2;
			variables[i] = 0;

			// change other variables
			for (int j = 0; j < id.size(); ++j) {
				
				// ignore the checking identifier
				if (j == i) continue;
		
				if (variables[j] == 0) {
					variables[j] = 1;
					break;
				} else {
					variables[j] = 0;
				}
			}
			// check if is 0
			bool all_zero = true;
			for (int j = 0; j < id.size(); ++j) {
				if (variables[j] == 1) {
					all_zero = false;
					break;
				}
			}
			if (all_zero) {
				break;
			}

			
		}

		if (not_change) {
			irrelevant_identifiers.push_back(id[i]);
			is_irrelevant_[index][i] = true;
		} else {
			is_irrelevant_[index][i] = false;
		}
	}

	return 0;
}