#include "Modifies.h"
#include "Clause.h"

Uses::Uses(argType _var1Type, string _var1, argType _var2Type, string _var2) :
Clause(relType::uses, _var1Type,  _var1,  _var2Type,  _var2) {
}

int Uses::getRelCase() {
    if (var1Type == argType::stmt && var2Type == argType::stmt) {
        relCase = 1;
        return relCase;
    } else if (var1Type == argType::stmt && var2Type == argType::variable){
        relCase = 2;
        return relCase;
    } else if (var1Type == argType::variable && var2Type == argType::stmt){
        relCase = 3;
        return relCase;
    } else if (var1Type == argType::variable && var2Type == argType::variable) {
        relCase = 4;
        return relCase;
    }
    
    return 0;
}