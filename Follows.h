#pragma once

#include "Clause.h"


class Follows: public Clause {
public:
	Follows(argType _var1Type, string _var1, argType _var2Type, string _var2);
    Follows(Clause clause);
    int getRelCase();
    
private:
};