#pragma once

#include "Clause.h"

class ParentS : public Clause {
public:
    ParentS(argType _var1Type, string _var1, argType _var2Type, string _var2);
    int getRelCase();
};