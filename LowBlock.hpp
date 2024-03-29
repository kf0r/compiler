#ifndef LOW_H
#define LOW_H
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <bitset>
#include "./Block.hpp"
#include "./Vertex.hpp"
#include "./ProgramStructure.hpp"

enum RegID{
    A,B,C,D,E,F,G,H
};

class LowInstruction{
public:
    std::string inst;
    int index;
    virtual std::string toString();
};

class ReturnMerger: public LowInstruction{
    std::string toString();
};

class Jumper: public LowInstruction{
public:
    LowInstruction* jumpTo;

    virtual std::string toString();

    virtual int test();
};

class JPos: public Jumper{
public:
    bool condition;

    int test();
};
class JZero: public Jumper{
public:
    bool condition;

    int test();

};

class Jump: public Jumper{
public:
    std::string where;

    int test();
};

class LowLevelBlock{
public:
    bool visited=false;
    int index;
    bool isCond;
    bool returning;
    ReturnMerger* merger;
    std::vector<LowInstruction*> instr;
    std::vector<Jumper*> jumpers;
    LowLevelBlock* next;
    LowLevelBlock* nextElse;
};


class Register{
public:
    int index;
    //std::string name;
    bool changed;
    bool locked;
    Value* stored;

    Register();
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

//sorry for my english its 1AM and its not my native language xd

//can be optimised to only stored changed variables in b,c,d,e,f, and store cached vars in g,h. 

class Architecture{
public:
    bool isMult = false;
    bool isDiv = false;
    unsigned long long counter;
    std::vector<Value*> garbageCollector;

    LowLevelBlock* currBlock;
    Program_part* programPart;

    Register regs[8];

    Architecture(Program_part* part);
    void setBlock(LowLevelBlock* block);
    void setCurrentPart(Program_part* part);
    void dumpAll();
    void dumpUnlocked();

    void storeAll();
    void storeReturn();
    void clearExplicit(int reg);
    void clearAll();

    int getVal(Value* val);
    void getInto(int i,Value* val);
    void getIntoA(Value* val);
    bool isSameVal(Value* first, Value* second);
    bool isCallable(Value* val);
    void forceClear();
    void buildAddress(Value* val, int where);
    int putModifiedVal(Value* val);
    int getBestFree();
    void storePrecheck(Identifier* id);
    void storePostcheck(Identifier* id);

    void buildNum(unsigned long long number, int where);
    void returnMerger();

    void add(int right);
    void sub(int right);

    void mult();
    void div();
    void mod();

    void read();
    void write();

    void rst(int reg);
    void dec(int reg);
    void inc(int reg);
    void shl(int reg);
    void shr(int reg);

    void put(int reg);
    void get(int reg);
    void load(int reg);
    void store(int reg);
    void strk(int reg);

    void jump(std::string procName);
    void jumpr(int reg);
    
    void jzero(bool cond);
    void jpos(bool cond);

    void haltMain();
};

class LowLevelProgram{
public:
    int index = 0;
    Architecture* arch;
    LowLevelBlock* mainBlock;
    std::map<int, LowLevelBlock*> mapBlock;
    std::map<std::string, LowLevelBlock*> proceduresBlock;
    Program* program;
    unsigned long long addr;
    unsigned long long prevAddr;


    LowLevelProgram(Program* whole);
    LowLevelBlock* generateLowBB(Block* block);
    std::vector<std::string> translate();

    void handleAssign(Assignment* assign);
    void handleRead(Read* read);
    void handleWrite(Write* write);
    void handleCond(Condition* cond);
    void handleCall(Procedure_call* call);

    //if in main, instrutuon HALT
    //if in procedure, dump only callable vars, build return addres, load, jump
    void handleReturn(); 
    void generateDiv();
    void generateMult();

    void setReturns(LowLevelBlock* lowBlock, Block* block);
    void link(LowLevelBlock* block);

    std::vector<std::string> generateAssembly();

    void getMachineCode(std::vector<LowInstruction*>& instructions, LowLevelBlock* block);
    static bool compareIndexes(LowInstruction* a, LowInstruction* b);
};


#endif