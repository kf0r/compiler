#include "./Types.hpp"
#include <iostream>

///////////////////////////////////////////////
//VALUE
///////////////////////////////////////////////
Identifier* Value::getIdentifier(){
    return nullptr;
}

bool Value::isArray(){
    return false;
}

///////////////////////////////////////////////
//IDENTIFIER
///////////////////////////////////////////////
Identifier* Identifier::getIdentifier(){
    return this;
}

bool Identifier::isArray(){
    return false;
}

unsigned long long Identifier::getOffset(){
    return 0;
}

///////////////////////////////////////////////
//IDENTIFIER ARR NUMBER
///////////////////////////////////////////////
Identifier* IndentifierArrNumber::getIdentifier(){
    return this;
}

bool IndentifierArrNumber::isArray(){
    return true;
}

unsigned long long IndentifierArrNumber::getOffset(){
    return stoi(address);
}

///////////////////////////////////////////////
//IDENTIFIER ARR PID
///////////////////////////////////////////////
Identifier* IndentifierArrPid::getIdentifier(){
    return this;
}

bool IndentifierArrPid::isArray(){
    return true;
}

///////////////////////////////////////////////
//DECLARATION
///////////////////////////////////////////////
bool Declaration::declare(Identifier* var){
    decsVec.push_back(var);
    ///std::cout<<var->val<<std::endl;
}

///////////////////////////////////////////////
//ARGS
///////////////////////////////////////////////
bool Args::addArg(Identifier* var){
    argsVec.push_back(var);
}