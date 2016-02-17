#pragma once

#include <vector>
#include <string>
#include <set>

#include "Clause.h"
#include "Modifies.h"
#include "ResultTable.h"
#include "Follows.h"
#include "FollowsS.h"
#include "Parent.h"
#include "ParentS.h"


using namespace std;

class Optimizer {
public: // Change later, for testing purposes

    vector<string> process(Clause clause);
	vector<string> process(Uses clause);
	vector<string> process(Modifies clause);
    vector<string> process(Parent clause);
    vector<string> process(ParentS clause);
    vector<string> process(Follows clause);
    vector<string> process(FollowsS clause);
	set<int> setUnion(set<int> set1, set<int> set2);
	set<int> setIntersect(set<int> set1, set<int> set2);
	// For Debugging
	void displaySet(set<int> set);

	Optimizer();
    void setSelectVar(string var);
private:
    string selectVar;
};