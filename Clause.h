#pragma once

#include <string>

using namespace std;

enum relType {
	uses, modifies, follows, followsS, parent, parentS
};

enum argType {
	procedure, stmt, assign, WHILE, IF, variable, CONSTANT, STRING, all
};

enum relCase {

};

class Clause {
public:
	Clause(relType rel, argType _var1Type, string _var1, argType _var2Type, string _var2);
    argType getVar1Type();
    argType getVar2Type();
    string getVar1();
	string getVar2();
    relType getRelType();
    
	void displayRelType();
protected:
	relType type;
	argType var1Type;
	argType var2Type;
	string var1;
	string var2;
	int relCase;
};