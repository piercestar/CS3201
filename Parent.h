#pragma once

#include "Clause.h"

class Parent : public Clause {
public:
    Parent(argType _var1Type, string _var1, argType _var2Type, string _var2);
    int getRelCase();
};