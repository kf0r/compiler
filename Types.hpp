#ifndef TYPES_H
#define TYPES_H

//#include "./Vertex.hpp"
#include <string>
#include <vector>
#include <set>

class Value{
public:
    std::string val;
    bool isArray = false; /////TODO: WYWALIC I ZAMIENIC NA FUNKCJE WIRTUALNA ZWRACAJACA NWM HGW CO
    virtual std::string getVar();
};

class Number: public Value{
public:
    //std::string getVar();
};

class Identifier: public Value{
public:
    virtual std::string getVar();
};

class IndentifierArrNumber: public Identifier{
public:
    bool isArray = true;
    std::string address;
    
};

class IndentifierArrPid: public Identifier{
public:
    bool isArray = true;
    std::string address;
};

class Expression{
public:
    Value* left;
    Value* right=nullptr;
};

class ExprSimple: public Expression{

};

class ExprComplex: public Expression{
public:
    
    std::string operand;
};

class Condition {
public:
    Value* leftVal;
    Value* rightVal;
    std::string operand;
};

class Declaration{
public:
    std::vector<Identifier*> decsVec;
    bool declare(Identifier* var);
};

class Args{
public:
    std::vector<Identifier*> argsVec;
    bool addArg(Identifier* var);
};

class Procedure_head{
public:
    Args* args;
    std::string name;

};

class Variable{
public:
    std::string id;
    bool isInitialized;
    unsigned long long adress;
    unsigned long long offset;
};

#endif