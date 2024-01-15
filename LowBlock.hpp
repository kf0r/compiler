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

    LowInstruction(std::string inst1, int target1);
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
    bool array;
    bool locked;
    Value* stored;

    Register(int i);
    void freeRegister();
    void setVal(Value* val);
};

class Architecture{
public:
    std::string currentPart;
    std::vector<Identifier*> garbageCollector;
    Register regs[8];

    Architecture();
    void dumpAll();
    void dumpUnlocked();

    int getVal(Value* val);
    void getInto(int i,Value* val);
    void getIntoA(Value* val);

    bool isSameVal(Value* first, Value* second);

    void buildNum(unsigned long long number, int where);

    void prepareToLoad(Value* val);

    int putValAnywhere(Value* val);

    int getBestFree();
};

class LowLevelProgram{
public:
    Architecture arch;
    LowLevelBlock* mainBlock;
    std::map<std::string, LowLevelBlock*> proceduresBlock;
    Program* program;
    unsigned long long addr;
    unsigned long long prevAddr;


    LowLevelProgram(Program* whole);
    void translateMain();
    void translateProcedure(std::string name);
};


#endif