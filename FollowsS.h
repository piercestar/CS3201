#pragma once

#include "Clause.h"


class FollowsS: public Clause {
public:
    FollowsS(argType _var1Type, string _var1, argType _var2Type, string _var2);
    int getRelCase();
    
private:
};