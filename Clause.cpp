#include <iostream>
#include <string>

#include "Clause.h"
#include "Modifies.h"
#include "Uses.h"
#include "Parent.h"
#include "ParentS.h"
#include "Follows.h"
#include "FollowsS.h"

using namespace std;



Clause::Clause(relType rel, argType _var1Type, string _var1, argType _var2Type, string _var2) {
		type = rel;
		var1Type = _var1Type;
		var2Type = _var2Type;
		var1 = _var1;
		var2 = _var2;
}

string Clause::getVar1() {
	return var1;
}

string Clause::getVar2() {
	return var2;
}

argType Clause::getVar1Type() {
    return var1Type;
}

argType Clause::getVar2Type() {
    return var2Type;
}

relType Clause::getRelType() {
    return type;
}

Modifies Clause::modifiesConverter(Clause clause) {
    Modifies converted = Modifies(clause);
    return converted;
}

Uses Clause::usesConverter(Clause clause) {
    Uses converted = Uses(clause);
    return converted;
}

Follows Clause::followsConverter(Clause clause) {
    Follows converted = Follows(clause);
    return converted;
}

FollowsS Clause::followsSConverter(Clause clause) {
    FollowsS converted = FollowsS(clause);
    return converted;
}

Parent Clause::parentConverter(Clause clause) {
    Parent converted = Parent(clause);
    return converted;
}

ParentS Clause::parentSConverter(Clause clause) {
    ParentS converted = ParentS(clause);
    return converted;
}

// For debugging
void Clause::displayRelType() {
	if (type == relType::modifies) {
		cout << "Modifies!" << endl;
	} else if (type == relType::follows) {
		cout << "Follows!" << endl;
    } else if (type == relType::followsS) {
		cout << "FollowsS!" << endl;
    } else if (type == relType::parent) {
        cout << "Parent!" << endl;
    } else if (type == relType::parentS) {
        cout << "ParentS!" << endl;
    } else if (type == relType::uses) {
        cout << "Uses!" << endl;
    }
}

	

