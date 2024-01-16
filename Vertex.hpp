#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include <map>
#include "./Types.hpp"
#include "./Block.hpp"

class Instruction{
public:
    Instruction();
    bool visited = false; //variable for DFS during semantic analisys
    bool isConditional = false;
    int blockIndex = -1;
    unsigned int index;
    Instruction* next;


    virtual bool isCall();
    virtual std::vector<Value*> getVars();
    virtual std::vector<Instruction*> getNext();
    virtual std::string print();
};

class Merger: public Instruction{
    std::string print();
};

class ConditionalSimple: public Instruction{
public:
    bool isConditional = true;
    Instruction* nextIfTrue;
    Condition* cond;

    std::vector<Value*> getVars();
    virtual std::vector<Instruction*> getNext();
    virtual std::string print();
};

class Conditional: public ConditionalSimple{
public:
    Instruction* nextIfFalse;
    std::vector<Instruction*> getNext();
    //std::string print();
};

class ConditionalWhile: public ConditionalSimple{
    //std::string print();
};

class ConditionalRepeat: public Conditional{
    //std::string print();

};

class Assignment: public Instruction{
public:
    Expression* expression;
    Identifier* identifier;

    std::vector<Value*> getVars();
    std::string print();
};

class Procedure_call: public Instruction{
public:
    Args* args;
    std::string name;

    std::vector<Value*> getVars();
    bool isCall();
    std::string print();
};

class Write: public Instruction{
public:
    Value* val;

    std::vector<Value*> getVars();
    std::string print();
};

class Read: public Instruction{
public:
    Identifier* ident;
    std::vector<Value*> getVars();
    std::string print();
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

class Program_part{
public:
    std::map<std::string, Variable*> symbolTable;
    Declaration* decs;
    LinkedCommands* comms;

    virtual void toString();
};

class Main: public Program_part{
    void toString();
};

class Procedure: public Program_part{
public:
    //std::map<std::string, Variable*> symbolTable;
    std::map<std::string, Variable*> callableTable;
    Procedure_head* head;
    unsigned long long initialAddr;
    unsigned long long retAddr;
    void toString();
    //LinkedCommands* comms;
    //Declaration* decs;
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