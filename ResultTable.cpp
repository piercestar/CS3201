#include <iostream>
#include <algorithm>
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
        vector<vector<string>> variableSet = getVariableSet(i);
        if (variableSet.size() > 1) {
            variableSet = mergeVariableSet(variableSet);
        }
        finalTable.push_back(getClauseSet(0,variableSet));
    }
    
}

vector<vector<string>> ResultTable::mergeVariableSet(vector<vector<string>> variableSet) {
    // start merging from back
    for (int i = variableSet.size() - 1; i > 0; i--) {
        vector<string> clauseToBeRemoved = getClauseSet(i, variableSet);
        vector<string> mergedClauseSet = getClauseSet(i-1, variableSet);
        vector<string>::iterator it = mergedClauseSet.begin();
        cout << "" << endl;
        while (it != mergedClauseSet.end()) {
            if (!contains(clauseToBeRemoved, (*it))) {
                it = (mergedClauseSet.erase(it));
            }
            else {
                it++;
            }
        }
        // remove last clause
        variableSet.at(i-1) = mergedClauseSet;
        variableSet.pop_back();
    }
    return variableSet;
}

list<string> ResultTable::getFinalResults() {
    list<string> finalResults;
    
    
    
    return finalResults;
}

void ResultTable::displayFinalTable() {
    vector<vector<string>>::iterator it = finalTable.begin();
    int index = 0;
    while( it != finalTable.end() ) {
        cout << endl;
        cout << "tuple number: " << index++ << endl;
        cout << "----------------------------------------------------------------" << endl;
        vector<string>::iterator it2 = (*it).begin();
        while (it2 != (*it).end()) {
            cout << *it2 << "," ;
            it2++;
        }
        cout << endl;
        it++;
    }
    
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

vector<string> ResultTable::getClauseSet(int clauseIndex, vector<vector<string>> variableSet) {
    vector<vector<string>>::iterator it = variableSet.begin();
    int index = 0;
    
    if (clauseIndex == variableSet.size() - 1) {
        return variableSet.back();
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
        return *it;
    }
    
}

vector<vector<string>> ResultTable::getVariableSet(int variableIndex) {
    vector<vector<vector<string>>>::iterator it = head.begin();
    int index = 0;
    while (it != head.end() && index != variableIndex) {
        index++;
        it++;
    }
    
    // not found
    if (index != variableIndex) {
        // TODO: Create not found enum
    }
    return *it;
}

// For testing purposes
int ResultTable::getNumTuples() {
    return head.size();
}

void ResultTable::displayResultTable() {
    for (int i = 0; i < getNumTuples(); i++) {
        cout << "Tuple set " << i << endl;
        vector<vector<string>> variableSet = getVariableSet(i);
		cout << "====================================================" << endl;
        for (int j = 0; j < variableSet.size(); j++) {
            vector<string> clauseSet = getClauseSet(j,variableSet);
            vector<string>::iterator it = clauseSet.begin();
            while (it != clauseSet.end()) {
                cout << *it << ",";
                it++;
            }
            cout << endl;
        }
		cout << "====================================================" << endl;
    }
}