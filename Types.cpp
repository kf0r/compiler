#include "./Types.hpp"
#include <iostream>
std::string Value::getVar(){
    return "";
}

std::string Identifier::getVar(){
    return val;
}

// std::string Number::getVar(){
//     return "";
// }

bool Declaration::declare(Identifier* var){
    decsVec.push_back(var);
    ///std::cout<<var->val<<std::endl;
}

bool Args::addArg(Identifier* var){
    argsVec.push_back(var);
}