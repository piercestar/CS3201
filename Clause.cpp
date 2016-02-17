#include <iostream>
#include <string>
#include "Clause.h"

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

// For debugging
void Clause::displayRelType() {
	if (type == relType::modifies) {
		cout << "Modifies!" << endl;
	}
	else if (type == relType::follows) {
		cout << "Follows!" << endl;
	}
}

	

