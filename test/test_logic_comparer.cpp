#include "logic_comparer.h"

#include <vector>

#include <gtest/gtest.h>



// expressions
const std::vector<std::vector<std::string>> kExpressions = {
	{"A", "A"},
	{"B", "A"},
	{"A|B", "B|A"},
	{"A&B", "B & A"},
	{"A|A", "A"},
	{"A&A", "A|A"},
	{"A & B", "A | B"},
	{"(A & B)", "A & B"},
	{"(A & B) | C", "(A | C) & (B | C)"},
	{"(A | B) & (C | D)", "(A&C) | (A&D) | (B&C) | (B&D)"},
	{"(A|B)&B", "B"},
	{"(A&B)|B", "B"}
};
// compare result
const std::vector<bool> kResult = {
	true,
	false,
	true,
	true,
	true,
	true,
	false,
	true,
	true,
	true,
	true,
	true
};


TEST(LogicComparerTest, Compare) {
	for (int i = 0; i < kExpressions.size(); ++i) {
		std::cout << "-----------"<< i << "----------" << std::endl;
		LogicComparer comparer;
		EXPECT_EQ(comparer.Compare(kExpressions[i][0], kExpressions[i][1]), kResult[i])
			<< "index " << i;
	}
}
