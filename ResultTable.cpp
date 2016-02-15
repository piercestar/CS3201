#include <iostream>
#include <iterator>
#include "ResultTable.h"

using namespace std;

ResultTable::ResultTable(int num_tuples) {
	for (int i = 0; i < num_tuples; i++) {
		vector<vector<string>> new_tuple;
		head.push_back(new_tuple);
	}
}

void ResultTable::addClauseSet(int tuple_index,vector<string> clauseSet) {
	// locate target tuple position
	vector<vector<vector<string>>>::iterator it = head.begin();
	int index = 0;
	while (index != tuple_index) {
		it++;
		index++;
	}
	// add clause set
	(*it).push_back(clauseSet);
}

// Merges all tables into a single final table for each tuple
void ResultTable::mergeTable() {
	// Merge 2 tables at a time until all tables have been merged for each tuple
	for (int i = 0; i < getNumTuples(); i++) {
		vector<vector<string>> variableSet = *getVariableSet(i);
		cout << "variableSet address: " << &variableSet << endl;
		if (variableSet.size() > 1) {
			cout << "before merge: " << variableSet.size() << endl;
			mergeVariableSet(variableSet);
			cout << &variableSet << endl;
			cout << "after merge: " << variableSet.size() << endl;
		}
	}
	
}

void ResultTable::mergeVariableSet(vector<vector<string>> &variableSet) {
	// start merging from back
	for (int i = variableSet.size() - 1; i > 0; i--) {
		vector<string> clauseToBeRemoved = *getClauseSet(i, variableSet);
		vector<string>* mergedClauseSetPtr = getClauseSet(i-1, variableSet);
		vector<string> mergedClauseSet = *mergedClauseSetPtr;
		vector<string>::iterator it = mergedClauseSet.begin();
		while (it != mergedClauseSet.end()) {
			if (!contains(clauseToBeRemoved, (*it))) {
				it = (mergedClauseSet.erase(it));
			}
			else {
				it++;
			}
		}
		cout << &variableSet << endl;
		// remove last clause
		variableSet.pop_back();
	}
}

list<string> ResultTable::getFinalResults() {
	list<string> finalResults = { "Final Results!" };

	return finalResults;
}

// internal modules

bool ResultTable::contains(vector<string> set, string element) {
	vector<string>::iterator it = set.begin();
	while (it != set.end()) {
		if (element.compare((*it)) == 0) {
			return true;
		}
		it++;
	}
	return false;
}

vector<string>* ResultTable::getClauseSet(int clauseIndex, vector<vector<string>> &variableSet) {
	vector<vector<string>>::iterator &it = variableSet.begin();
	int index = 0;
	
	if (clauseIndex == variableSet.size() - 1) {
		return &(variableSet.back());
	}
	else {
		while (it != variableSet.end() && index != clauseIndex) {
			index++;
			it++;
		}

		// not found
		if (index != clauseIndex) {
			// TODO: Create not found enum
		}
		return &(*it);
	}

}

vector<vector<string>>* ResultTable::getVariableSet(int variableIndex) {
	vector<vector<vector<string>>>::iterator& it = head.begin();
	int index = 0;
	while (it != head.end() && index != variableIndex) {
		index++;
		it++;
	}

	// not found
	if (index != variableIndex) {
		// TODO: Create not found enum
	}
	cout << variableIndex << " pointer address: " <<  &(*it) << endl;
	return &(*it);
}

// For testing purposes
int ResultTable::getNumTuples() {
	return head.size();
}

void ResultTable::displayResultTable() {
	for (int i = 0; i < getNumTuples(); i++) {
		cout << "Tuple set " << i << endl;
		vector<vector<string>>* variableSetPtr = getVariableSet(i);
		vector<vector<string>> variableSet = *variableSetPtr;

		for (int j = 0; j < variableSet.size(); j++) {
			cout << "====================================================" << endl;
			vector<string> clauseSet = *getClauseSet(j,variableSet);
			vector<string>::iterator it = clauseSet.begin();
			while (it != clauseSet.end()) {
				cout << *it << ",";
				it++;
			}
			cout << endl;
			cout << "====================================================" << endl;
		}
	}
}