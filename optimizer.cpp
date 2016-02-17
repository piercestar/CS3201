#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

#include "Optimizer.h"
#include "ResultTable.h"

using namespace std;

// Optimizer
Optimizer::Optimizer() {

}

// Optimizes PKB querying

// Pass in Clause
// Utilize module based on relationship type

// Try out overloading
// Test succesfull including overloading parent class.

// Set comparer(set1, set2)

// SetUnion
set<int> Optimizer::setUnion(set<int> set1, set<int> set2) {
	set1.insert(set2.begin(), set2.end());
	return set1;
}

// SetIntersection
set<int> Optimizer::setIntersect(set<int> set1, set<int> set2) {
	set<int> result;
	set_intersection(set1.begin(),set1.end(),set2.begin(),set2.end(),inserter(result,result.begin()));
	return result;
}

// Set printer
void Optimizer::displaySet(set<int> toDisplay) {

	cout << "Set: ";
	set<int>::iterator it = toDisplay.begin();
	while (it != toDisplay.end()) {
		cout << *it << ",";
		it++;
	}
	cout << endl;
}

// MODULE NOT TESTED
vector<string> vectorConverter(set<int> toConvert) {
	set<int>::iterator it = toConvert.begin();
	vector<string> converted;

	while (it != toConvert.end()) {
		converted.push_back(to_string(*it));
		it++;
	}

	return converted;
}

ResultTable Optimizer::process(Modifies clause,ResultTable resultTable) {
	int relCase = clause.getRelCase;
	
	if (relCase = 1) {
		//(Constant1,Constant2) case : 
		// use var1 to get constant2 set of values
		set<int> constant2Set = PKB::modifies(argType::stmt, clause.getVar1()); // Note, Uses(variable) <- variable is 1st or 2nd argument? Assuming that it is the first,
		// look for var1 in constant1 set
		if (constant2Set.find(clause.getVar1) != constant2Set.end()) {
			// Does this work if set var is the last element?
			// Create result vector
			vector<string> clauseSet;
			clauseSet.push_back("0"); // 0 Denotes boolean true
			// Add result vector to resultTable
			resultTable.addClauseSet(0,clauseSet);
		}
		else {
			// No values
			vector<string> clauseSet;
			clauseSet.push_back("-1"); // -1 denotes boolean false;
			resultTable.addClauseSet(0, clauseSet);
		}
	}
	else if (relCase = 2) {
		//(Constant1, Variable2)
		set<int> variable2Set = PKB::modifies(argType::stmt, clause.getVar1());
		// Need extra set for non-stmt variables like (assign a)
		
		vector<string> clauseSet = vectorConverter(variable2Set);
		resultTable.addClauseSet(0, clauseSet);
	}
	else if (relCase = 3) {
		//(stmt, Constant2)
		// get stmt list
		set<int> stmtLst;
		// manually check if stmt contains constant
		set<int>::iterator it = stmtLst.begin();
		vector<string> clauseSet;
		while (it != stmtLst.end()) {
			set<int> constant2Set = PKB::modifies(argType::stmt, *it);
			if (constant2Set.find(clause.getVar2) != constant2Set.end()) {
				// constant found, add stmt to clause set
				clauseSet.push_back(to_string(*it));
			}
			it++;
		}
		// clauseSet complete, add to result table
		resultTable.addClauseSet(0,clauseSet);
	}
	else if (relCase = 4) {
		// (stmt,variable2)
		// get all stmts
		set<int> stmtLst;
		// get all stmt sets and keep on merging
		set<int>::iterator it = stmtLst.begin();
		vector<string> clauseSet;
		set<int> resultSet;
		while (it != stmtLst.end()) {
			set<int> variable2Set = PKB::modifies(argType::stmt, *it);
			resultSet = setUnion(resultSet, variable2Set);
			it++;
		}
		// return final set
		resultTable.addClauseSet(0, vectorConverter(resultSet));
	}

	return resultTable;
}

ResultTable Optimizer::process(Follows clause, ResultTable resultTable) {

}