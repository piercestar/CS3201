#include "Follows.h"

Follows::Follows(Clause clause)
	:Clause(relType::follows, clause.getVar1Type(), clause.getVar1(), clause.getVar2Type(), clause.getVar2()) {

}

Follows::Follows(argType _var1Type, string _var1, argType _var2Type, string _var2)
:Clause(relType::follows, _var1Type, _var1, _var2Type, _var2) {
    
}

int Follows::getRelCase(){
    
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


