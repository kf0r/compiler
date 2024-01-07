#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include <map>
#include "./Types.hpp"

class Instruction{
public:
    Instruction();
    bool visited = false; //variable for DFS during semantic analisys
    bool isConditional = false;
    unsigned int index;
    Instruction* next;

    virtual std::vector<std::string> getVars();
    virtual std::vector<Instruction*> getNext();
};

class ConditionalSimple: public Instruction{
public:
    bool isConditional = true;
    Instruction* nextIfTrue;
    Condition* cond;
    std::vector<std::string> getVars();
    virtual std::vector<Instruction*> getNext();
};

class Conditional: public ConditionalSimple{
public:
    Instruction* nextIfFalse;
    std::vector<Instruction*> getNext();
};

class ConditionalWhile: public ConditionalSimple{

};

class ConditionalRepeat: public ConditionalSimple{

};

class Assignment: public Instruction{
public:
    Expression* expression;
    Identifier* identifier;

    std::vector<std::string> getVars();
};

class Procedure_call: public Instruction{
public:
    Args* args;
    std::string name;

    std::vector<std::string> getVars();
};

class Write: public Instruction{
public:
    Value* val;

    std::vector<std::string> getVars();
};

class Read: public Instruction{
public:
    Identifier* ident;

    std::vector<std::string> getVars();
};

class LinkedCommands{
public:
    Instruction* head;
    Instruction* tail;

    LinkedCommands();
    void addInst(Instruction* inst); //Przejsc po nextach inst az bedzie null i ten bedzie tailem 
    Instruction* getHead();
    Instruction* getTail(); 
};

class Main{
public:
    std::map<std::string, Variable*> symbolTable;
    Declaration* decs;
    LinkedCommands* comms;
};

class Procedure{
public:
    std::map<std::string, Variable*> symbolTable;
    std::map<std::string, Variable*> callableTable;
    Procedure_head* head;
    LinkedCommands* comms;
    Declaration* decs;
};

class ProcedureComplex: public Procedure{
public:
};

class ProceduresAll{
public:
    std::vector<Procedure*> procedures;
    bool addProc(Procedure* proc);
};

#endif