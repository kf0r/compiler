#include "./Types.hpp"

bool Declaration::declare(Identifier* var){
    decs.push_back(var);
}

bool Args::addArg(Identifier* var){
    argsVec.push_back(var);
}