#include "./Types.hpp"
#include <iostream>
bool Declaration::declare(Identifier* var){
    decsVec.push_back(var);
    ///std::cout<<var->val<<std::endl;
}

bool Args::addArg(Identifier* var){
    argsVec.push_back(var);
}