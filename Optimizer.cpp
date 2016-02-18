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
            return process(clause.modifiesConverter(clause));
            break;
        case uses:
            return process(clause.usesConverter(clause));
			break;
		case follows:
			return process(clause.followsConverter(clause));
			break;
		case followsS:
			return process(clause.followsSConverter(clause));
			break;
		case parent:
			return process(clause.parentConverter(clause));
			break;
		case parentS:
			return process(clause.parentSConverter(clause));
			break;
        default:
            break;
    }
    
}


vector<string> Optimizer::process(Uses clause) {

	int relCase = clause.getRelCase();
	vector<string> clauseSet;
	switch (relCase) {
	case 1:
		// (defined, defined)
		set<int> usedByEntity = PKB::uses(clause.getVar1Type(), clause.getVar2());
		set<int>::iterator find = usedByEntity.find(stoi(clause.getVar1()));
		if (find != usedByEntity.end()) {
			// found
			clauseSet.push_back("0");
		}
		else {
			clauseSet.push_back("-1");
		}
		return clauseSet;
		break;
	case 2:
		// (defined, var)
		EntityType type = clause.getVar1Type();
		switch (type) {
		case EntityType::PROCEDURE:
			set<int> usedByProc = ProcTable::getVarUsedByProc(ProcTable::getProcIndex(clause.getVar1()));
			for (set<int>::iterator it = usedByProc.begin(); it != usedByProc.end(); ++it) {
				clauseSet.push_back(to_string(*it));
			}
			break;
		case EntityType::ASSIGN:
			set<int> usedByStmt = StmtTable::getStmtUses(stoi(clause.getVar1()));
			set<int> assignStmts = StmtTable::getAssignStmts();
			set<int> usedByAssign = setIntersect(usedByStmt, assignStmts);
			for (set<int>::iterator it = usedByAssign.begin(); it != usedByAssign.end(); ++it) {
				clauseSet.push_back(to_string(*it));
			}
			break;
		case EntityType::WHILE:
			set<int> usedByStmt = StmtTable::getStmtUses(stoi(clause.getVar1()));
			set<int> whileStmts = StmtTable::getWhileStmts();
			set<int> usedByWhile = setIntersect(usedByStmt, whileStmts);
			for (set<int>::iterator it = usedByWhile.begin(); it != usedByWhile.end(); ++it) {
				clauseSet.push_back(to_string(*it));
			}
			break;
		case EntityType::STMT:
			set<int> usedByStmt = StmtTable::getStmtUses(stoi(clause.getVar1()));
			for (set<int>::iterator it = usedByStmt.begin(); it != usedByStmt.end(); ++it) {
				clauseSet.push_back(to_string(*it));
			}
			break;
		default:
			;
		}
		break;
	case 3:
		// (stmt, defined)
		set<int> usedByEntity = PKB::uses(clause.getVar1Type(), clause.getVar2());
		for (set<int>::iterator it = usedByEntity.begin(); it != usedByEntity.end(); ++it) {
			clauseSet.push_back(to_string(*it));
		}

		return clauseSet;
		break;
	case 4:
		// (stmt, stmt)
		// TODO
		set<int> childrenOfStmt1 = PKB::getChild(clause.getVar1());
		set<int> parentsOfStmt = PKB::getParent(clause.getVar2());
		
		return clauseSet;
		break;
	default:
		;
	}
}

vector<string> Optimizer::process(Modifies clause) {
	int relCase = clause.getRelCase();
    vector<string> clauseSet;
    
	if (relCase == 1) {
		//(defined1,defined2) case :
		// use var1 to get defined2 set of values
		set<int> defined2Set = PKB::modifies(clause.getVar1Type(), clause.getVar1());
        // look for var1 in defined1 set
		if (defined2Set.find(stoi(clause.getVar1())) != defined2Set.end()) {
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
			if (constant2Set.find(stoi(clause.getVar2())) != constant2Set.end()) {
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
				stmtLst = PKB::get;// What is the API for stmt?
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
		
			PKB::getFollow(*it);
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
            set<int> stmt2Set = PKB::getFollowStar(clause.getVar1());
            clauseSet = vectorConverter(stmt2Set);
            return clauseSet;
            break;
        case 3:
            // (stmt1, defined)
            set<int> stmt1Set = PKB::isFollowByStar(clause.getVar2());
            clauseSet = vectorConverter(stmt2Set);
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
            if (PKB::isParent(clause.getVar1(), clause.getVar2())) {
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
            if (PKB::isParentStar(clause.getVar1(), clause.getVar2())) {
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