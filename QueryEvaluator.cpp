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
	ResultTable resultTable = ResultTable::ResultTable(selectVar.size());
    bool isVarUsed = false;
    Optimizer optimizer = Optimizer::Optimizer();
    
    // Get Select Clause
    vector<Clause>::iterator it = selectVar.begin();
	for (int i = 0; i < selectVar.size(); i++) {
		Clause selectClause = *it;
		string varName = selectClause.getVar1();
		optimizer.setSelectVar(varName);

		// get Clauses from rel
		vector<Clause>::iterator rel_it = rel.begin();
		while (rel_it != rel.end()) {
			Clause currClause = *it;
			vector<string> clauseSet;

			// determine if select clause is used
			if (varName.compare(currClause.getVar1()) != 0 || varName.compare(currClause.getVar2()) != 0) {
				// not used, query result anyways but if clause is empty/false, final result = empty
				clauseSet = optimizer.process(currClause);
				if (clauseSet.size() == 0) {
					// Hard fix
					return result;
				}
			}
			else {
				// used, query and add
				clauseSet = optimizer.process(currClause);
				resultTable.addClauseSet(0, clauseSet);
				isVarUsed = true;
			}
			it++;
		}
	}
	resultTable.mergeTable();
	result = resultTable.getFinalResults();

	// Check if Select variable is used. 
	if (isVarUsed == false) {
		list<string> empty;
		// not used, check if true/false and return results
		if (result.size() == 0) {
			//false
			return empty;
		} else if ((*result.begin()).compare("-1")) {
			// false
			return empty;
		}
		else {
			// true, return all values of selectVar
		}
	}
    
	

    // Return List<string> (This will allow both variables and integers and boolean to be output as result without the need for seperate functions)
    return result;
}

