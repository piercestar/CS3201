#include <string>
#include <list>
#include <vector>
#include "Clause.h"
#include "QueryEvaluator.h"
#include "ResultTable.h"
#include "Optimizer.h"

using namespace std;

// Query Evaluator
QueryEvaluator::QueryEvaluator() {
    
}

list<string> QueryEvaluator::evaluate(vector<Clause> rel, vector<Clause> selectVar, vector<Pattern> pattern) {
    
    list<string> result;
    vector<ResultTable> resultList;
    bool isVarUsed = false;
    Optimizer optimizer = Optimizer::Optimizer();
    
    // Get Select Clause
    vector<Clause>::iterator it = selectVar.begin();
    for (int i=0; i<selectVar.size(); i++) {
        Clause selectClause = *it;
        string varName = selectClause.getVar1();
        optimizer.setSelectVar(varName);
    
        // get Clauses from rel
        vector<Clause>::iterator rel_it = rel.begin();
        while(rel_it != rel.end()) {
            Clause currClause = *it;
            vector<string> clauseSet;
            
            // determine if select clause is used
            if (varName.compare(currClause.getVar1()) != 0 || varName.compare(currClause.getVar2()) != 0) {
                // not used, query result anyways but if clause is empty/false, final result = empty
                clauseSet = optimizer.process(currClause);
            } else {
                // used, query and add
                clauseSet = optimizer.process(currClause);
            }
        }
        
    // Do comparison with each clause to determine if clause contains the query required
    for (int i = 0; i < selectVar.size(); i++) {
        Clause currentClause = queryTree.getClause(i);
        if (currentClause.contains(selectClause)) {
            // If clause is necessary for the query result, call on generic process clause function, else move on to next clause
            // Generic process clause is an overloaded function that has the clause relationship type as it's unique identifier
            ResultTable clauseResult = process(currentClause,currentClause.getType());
            // Add results to the result list
            resultList.push_back(clauseResult);
        }
    }
    
    // Merge table function will search for all common elements and condense them into the finalTable
    ResultTable finalTable = mergeTable(resultList);
    
    // Extract results from finalTable into a List<string> format
    result = extractResults(finalTable);
    
    // Return List<string> (This will allow both variables and integers and boolean to be output as result without the need for seperate functions)
    return result;
}

// Each overloaded function handles it's own seperate relationship type and returns results in the form of a ResultTable.

