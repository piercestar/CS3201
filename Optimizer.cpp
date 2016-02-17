#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

#include "Optimizer.h"
#include "ResultTable.h"
#include "Clause.h"
#include "Uses.h"

using namespace std;

// Optimizer
Optimizer::Optimizer() {

}

void Optimizer::setSelectVar(string _selectVar) {
    selectVar = _selectVar;
}

//
//// Optimizes PKB querying
//
//// Pass in Clause
//// Utilize module based on relationship type
//
//// Try out overloading
//// Test succesfull including overloading parent class.
//
//// Set comparer(set1, set2)

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

vector<string> Optimizer::process(Clause clause) {
    // Get clause type
    relType type = clause.getRelType();

    
    switch (type) {
        case modifies:
            Modifies &castedClause = dynamic_cast<Modifies&>(clause);
            process(castedClause);
            break;
        case uses:
            Uses &castedClause = dynamic_cast<Uses&>(clause);
            process(castedClause);
            
        default:
            break;
    }
    
}

vector<string> Optimizer::process(Modifies clause) {
	int relCase = clause.getRelCase();
    vector<string> clauseSet;
    
	if (relCase == 1) {
		//(defined1,defined2) case :
		// use var1 to get defined1 set of values
		set<int> defined2Set = PKB::modifies(clause.getVar1Type(), clause.getVar1());
        // look for var1 in defined1 set
		if (defined2Set.find(clause.getVar1()) != defined2Set.end()) {
			// Does this work if set var is the last element?
			// Create result vector
			clauseSet.push_back("0"); // 0 Denotes boolean true
            return clauseSet;
		}
		else {
			// No values
			clauseSet.push_back("-1"); // -1 denotes boolean false;
            return clauseSet;
		}
	}
	else if (relCase == 2) {
		//(defined1, Variable2)
		set<int> variable2Set = PKB::modifies(clause.getVar1Type(), clause.getVar1());
		// Need extra set for non-stmt variables like (assign a)
		
		clauseSet = vectorConverter(variable2Set);
        return clauseSet;
	}
	else if (relCase == 3) {
		//(stmt, defined2)
		// get stmt list
		set<int> stmtLst;
		// manually check if stmt contains constant
		set<int>::iterator it = stmtLst.begin();
		vector<string> clauseSet;
		while (it != stmtLst.end()) {
			set<int> constant2Set = PKB::modifies(argType::stmt, *it);
			if (constant2Set.find(clause.getVar2()) != constant2Set.end()) {
				// constant found, add stmt to clause set
				clauseSet.push_back(to_string(*it));
			}
			it++;
		}
        return clauseSet;
	}
	else if (relCase == 4) {
		// (stmt,variable2)
		// get all stmts
		set<int> stmtLst;
		// get all stmt sets and keep on merging
        argType stmt1Type = clause.getVar1Type();
        switch (stmt1Type) {
            case assign:
                stmtLst = PKB::getAssignStmts();
                break;
            case stmt:
                stmtLst = PKB::get  // What is the API for stmt?
                break;
            case WHILE:
                stmtLst = PKB::getWhileStmts();
                break;
            default:
                break;
        }
		set<int>::iterator it = stmtLst.begin();
		vector<string> clauseSet;
		set<int> resultSet;
		while (it != stmtLst.end()) {
			set<int> variable2Set = PKB::modifies(stmt1Type, *it);
			resultSet = setUnion(resultSet, variable2Set);
			it++;
		}
		// return final set
		clauseSet = vectorConverter(resultSet);
        return clauseSet;
	}
}

vector<string> Optimizer::process(Follows clause) {

    int  relCase = clause.getRelCase();
    vector<string> clauseSet;
    
    if (relCase == 1) {
        // (defined1,defined2)
        if (PKB::getFollow(clause.getVar1()) == clause.getVar2()) {
            clauseSet.push_back("0"); // 0 Denotes boolean true
            return clauseSet;
        }
        else {
            // No values
            clauseSet.push_back("-1"); // -1 denotes boolean false;
            return clauseSet;
        }
        
    } else if (relCase == 2) {
        // (defined1, stmt2)
        clauseSet.push_back(PKB::getFollow(clause.getVar1()));
        return clauseSet;
        
    } else if (relCase == 3) {
        // (stmt1, defined2)
        clauseSet.push_back(PKB::getFollow(clause.getVar2()));
        return clauseSet;
        
    } else if (relCase == 4) {
        // (stmt1, stmt2)
        set<int> stmtLst;
        // manually obtain follows set
        vector<string> clauseSet;
        set<int>::iterator it = stmtLst.begin();
        while (it != stmtLst.end()) {
            clause
            PKB::getFollow(*it)
            it++;
        }
        // Need to know what is the Select variable in order to do
        
    }
    
}

vector<string> Optimizer::process(FollowsS clause) {
    
    int relCase = clause.getRelCase();
    vector<string> clauseSet;
    switch (relCase) {
        case 1:
            // (defined, defined)
            if (PKB::isFollowStar(clause.getVar1(),clause.getVar2())) {
                clauseSet.push_back("0"); // 0 Denotes boolean true
                // Add result vector to resultTable
                return clauseSet;
            } else {
                // No values
                clauseSet.push_back("-1"); // -1 denotes boolean false;
                return clauseSet;
            }
            break;
        case 2:
            // (defined, stmt2)
            set<int> stmt2Set() = PKB::getFollowStar(clause.getVar1());
            clauseSet = vectorConverter(stmt2Set());
            return clauseSet;
            break;
        case 3:
            // (stmt1, defined)
            set<int> stmt1Set() = PKB::isFollowByStar(clause.getVar2());
            clauseSet = vectorConverter(stmt2Set());
            return clauseSet;
            break;
        case 4:
            // (stmt, stmt)
            
            // Need to know what is the Select variable
            break;
        default:
            ;
    }
}

vector<string> Optimizer::process(Parent clause) {
    
    int relCase = clause.getRelCase();
    vector<string> clauseSet;
    switch (relCase) {
        case 1:
            // (defined, defined)
            if (isParent(clause.getVar1(), clause.getVar2())) {
                clauseSet.push_back("0");
            } else {
                clauseSet.push_back("-1");
            }
            return clauseSet;
            break;
        case 2:
            // (defined, stmt)
            set<int> stmt1Children = PKB::getChild(clause.getVar1());
            clauseSet = vectorConverter(stmt1Children);
            return clauseSet;
            break;
        case 3:
            // (stmt, defined)
            int stmt2Parent = PKB::getParent(clause.getVar2());
            clauseSet.push_back(stmt2Parent);
            return clauseSet;
            break;
        case 4:
            // (stmt, stmt)
            set<int> childrenOfStmt1 = PKB::getChild(clause.getVar1());
            set<int> parentsOfStmt = PKB::getParent(clause.getVar2());
            break;
        default:
            ;
    }
}

vector<string> Optimizer::process(ParentS clause) {
    
    int relCase = clause.getRelCase();
    vector<string> clauseSet;
    switch (relCase) {
        case 1:
            // (defined, defined)
            if (isParentStar(clause.getVar1(), clause.getVar2())) {
                clauseSet.push_back("0");
            } else {
                clauseSet.push_back("-1");
            }
            return clauseSet;
            break;
        case 2:
            // (defined, stmt)
            set<int> stmt1Children = PKB::getChildStar(clause.getVar1());
            clauseSet = vectorConverter(stmt1Children);
            return clauseSet;
            break;
        case 3:
            // (stmt, defined)
            set<int> stmt2Parents = PKB::getParentStar(clause.getVar2());
            clauseSet = vectorConverter(stmt2Parents);
            return clauseSet;
            break;
        case 4:
            // (stmt, stmt)
            set<int> childrenOfStmt1 = PKB::getChild(clause.getVar1());
            set<int> parentsOfStmt = PKB::getParent(clause.getVar2());
            break;
        default:
            ;
    }	
}