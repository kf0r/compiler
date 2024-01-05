#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include <map>
#include "./Types.hpp"

class Instruction{
public:
    Instruction();
    bool isConditional = false;
    unsigned int index;
    Instruction* next;
};

class Conditional: public Instruction{
public:
    bool isConditional = true;
    Instruction* nextIfFalse;
    Instruction* nextIfTrue;
    std::string type;
    std::string left;
    std::string evaluator;
    std::string right;
};

class ConditionalSimple: public Instruction{
public:
    bool isConditional = true;
    Instruction* nextIfTrue;
    std::string type;
    std::string left;
    std::string evaluator;
    std::string right;
};

class ConditionalWhile: public ConditionalSimple{

};

class ConditionalRepeat: public ConditionalSimple{

};

// class AssignmentSimple: Instruction{
// public:
//     std::string target;
//     std::string left;
// };

class Assignment: public Instruction{
public:
    Expression* expression;
    Identifier* identifier;
};

class Procedure_call: public Instruction{
public:
    Args* args;
    std::string name;
};

class Write: public Instruction{
public:
    Value* val;
};

class Read: public Instruction{
public:
    Identifier* ident;
};

class LinkedCommands{
public:
    Instruction* head;
    Instruction* tail;

    LinkedCommands();
    void addInst(Instruction* inst); //Przejsc po nextach inst az bedzie null i ten bedzie tailem byq
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
    std::map<std::string, Variable*> declarationTable;
    Procedure_head* head;
    LinkedCommands* comms;
    Declaration* decs = nullptr;
};

class ProcedureComplex: public Procedure{
public:
   Declaration* decs;
};

class ProceduresAll{
public:
    std::vector<Procedure*> procedures;
    bool addProc(Procedure* proc);
};

#endif