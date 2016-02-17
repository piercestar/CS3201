#pragma once

#include "Clause.h"

class Modifies : public Clause {
public:
	Modifies(argType _var1Type, string _var1, argType _var2Type, string _var2);
	int getRelCase();
};