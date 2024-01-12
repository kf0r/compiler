#ifndef TYPES_H
#define TYPES_H

//#include "./Vertex.hpp"
#include <string>
#include <vector>
#include <set>
class Identifier;

class Value{
public:
    std::string val;
    //bool isArray = false; /////TODO: WYWALIC I ZAMIENIC NA FUNKCJE WIRTUALNA ZWRACAJACA NWM HGW CO
    virtual Identifier* getIdentifier();
    virtual bool isArray();
};

class Number: public Value{
public:
    //std::string getVar();
};

class Identifier: public Value{
public:
    virtual Identifier* getIdentifier();
    virtual unsigned long long getOffset();
    virtual bool isArray();
};

class IndentifierArrNumber: public Identifier{
public:
    //bool isArray = true;
    Identifier* getIdentifier();
    std::string address;
    unsigned long long getOffset();
    bool isArray();
};

class IndentifierArrPid: public Identifier{
public:
    //bool isArray = true;
    Identifier* getIdentifier();
    std::string address;
    bool isArray();
};

class Expression{
public:
    Value* left;
    Value* right=nullptr;

    virtual void test();
};

class ExprSimple: public Expression{
public:
    void test();
};

class ExprComplex: public Expression{
public:
    std::string operand;
    void test();
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
    bool isInitialized=false;
    bool isOffsettable;
    unsigned long long adress;
    unsigned long long offset = 0;
};

#endif