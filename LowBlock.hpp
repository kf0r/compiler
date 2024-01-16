#ifndef LOW_H
#define LOW_H
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "./Block.hpp"
#include "./Vertex.hpp"
#include "./ProgramStructure.hpp"

class LowInstruction{
public:
    std::string inst;
    int target;
};

class Builder: public LowInstruction{
public:
    unsigned long long numberBuild;
};

class Multiplier: public LowInstruction{
public:
    int rightTarget;
};
class Modulator: public LowInstruction{
public:
    int rightTarget;
};
class Divider: public LowInstruction{
public:
    int rightTarget;
};
class Jumper: public LowInstruction{
public:
    int rightTarget;
};
class LowLevelBlock{
public:
    int index;
    std::vector<LowInstruction*> instr;
    LowLevelBlock* next;
};

class LowConditional: public LowLevelBlock{
public:
    LowConditional* elseNext;
};

class Register{
public:
    int index;
    std::string name;
    bool changed;
    bool locked;
    Value* stored;

    Register(int i);
    void freeRegister();
    void setVal(Value* val);
};

//register "a" is for building addresses of simple values
//register "h" is for building addresses of arrays, it will be added to "a" and loaded to get array

//when calling fuction with given parameter you are actually give it a pointer to given value
//loading pointers: address where pointer is stored is build in a, pointer is loaded into a.
//if pointer was pointing to array, like x[z] pointer will be stored in "h", and value z will be loaded into "a"
//grammar forbids expressions like x[x[z]], so its not a problem if z was also a pointer. 
//After building address of z in a, we can load a once (if z was in symbolTable) or twice (if z was in callableTable)
//then we add h and get pointer to actual value that can be loaded into a and manipulated as we wish

//register "g" is a emergency register.
//if all "unordinary" registers are storing elements of arrays, and register a stores results of some operation, we cant afford to lose it
//we have to free one register, containing changed value of x[z].
//to build address of x, we still have register "h", but theres no way to build or load z and add it to h to store x[z], because "a" contains changed variable
//to escape this issue we put f. Now register a is free to build addresses to free register.

//sorry for my english its 1AM and its not my native language xd.

//important optimisation - dont store variables in symbol table before returning.
class Architecture{
public:
    std::vector<Value*> garbageCollector;
    Program_part* programPart;

    Register regs[8];

    Architecture(Program_part* part);
    void dumpAll();
    void dumpUnlocked();
    int getVal(Value* val);
    void getInto(int i,Value* val);
    void getIntoA(Value* val);
    bool isSameVal(Value* first, Value* second);
    bool isCallable(Value* val);
    void buildNum(unsigned long long number, int where);
    void buildAddress(Value* val, int where);
    int putModifiedVal(Value* val);
    int getBestFree();

    void add();
    void sub();
    void rst();
    void dec();
    void inc();
    void shl();
    void shr();

    void put();
    void get();
    void load();
    void store();
    void strk();

    void jump();
    void jzero();
    void jpos();
    void jumpr();
};

class LowLevelProgram{
public:
    Architecture* arch;
    LowLevelBlock* mainBlock;
    std::map<std::string, LowLevelBlock*> proceduresBlock;
    Program* program;
    unsigned long long addr;
    unsigned long long prevAddr;


    LowLevelProgram(Program* whole);
    void translateMain();
    void translateProcedure(std::string name);

    void handleAssign();
    void handleWrite();
    void handleRead();
    void handleCond();
    void handleCall();
};


#endif