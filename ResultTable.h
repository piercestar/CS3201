#include <vector>
#include <string>
#include <list>

using namespace std;

#ifndef ResultTable_H
#define ResultTable_H

class ResultTable {
private:
	vector<vector<vector<string>>> head;

	// internal modules
	vector<string>* getClauseSet(int clauseIndex, vector<vector<string>> &variableSet);
	vector<vector<string>>* getVariableSet(int variableIndex);
	bool contains(vector<string> set, string element);

public:
	ResultTable(int num_tuples);
	void addClauseSet(int tuple_index,vector<string> clauseSet);
	void mergeTable();
	void mergeVariableSet(vector<vector<string>> &variableSet);
	list<string> getFinalResults();
	// Test modules
	int getNumTuples();
	void displayResultTable();

};


#endif

