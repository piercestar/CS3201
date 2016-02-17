#pragma once

#include <vector>
#include <string>
#include <set>

#include "Clause.h"
#include "Modifies.h"

using namespace std;

class Optimizer {
public: // Change later, for testing purposes

	ResultTable process(Modifies clause,ResultTable resultTable);
	ResultTable process(Follows clause, ResultTable resultTable);
	set<int> setUnion(set<int> set1, set<int> set2);
	set<int> setIntersect(set<int> set1, set<int> set2);
	// For Debugging
	void displaySet(set<int> set);

	Optimizer();
};