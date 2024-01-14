#ifndef LOW_H
#define LOW_H
#include <vector>
#include <string>
#include "./Block.hpp"
#include "./Architecture.hpp"
#include "./Vertex.hpp"
#include "./ProgramStructure.hpp"

unsigned long long MAX_MEM_SIZE = 4611686018427388000;
const int ASCII_LOWER_A = 97;

////////
//IDEA//
////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//registers "a" and e are special, "a" because its loads, stores, puts and gets                      //
//"e" because it will build addresses and values                                                     //
//when getting variable, its value will be builded in "e" and variable will be loaded into "a"       //
//if theres no free register, one unlocked register will be freed and variable will be stored there. //
//                                                                                                   //
//when getting array, it will be checked if index of variable is already in register.                //
//If it is, adress will be builded in "a" and added to index, loaded, put into free register,        //
//after operation on indexed array register is freed                                                 //
//                                                                                                   //
//when getting array numbered, we tread it as normal variable, but also contain number in indexStored//
///////////////////////////////////////////////////////////////////////////////////////////////////////
class Register{
public:
    int number;
    char index;

    //lock during operations, so architecture wouldnt free register thats currently in use
    bool locked;
    bool changed; //if has changed then store during dump

    Value* stored;
    std::string indexStored;
};  

class LowLevelBlock{
public:
    std::vector<std::string> lowInstructions;
    int index; 
    LowLevelBlock* next;
}; 

class LowConditional: public LowLevelBlock{
public:
    LowLevelBlock* elseNext;
};

class LowLevelProgram{
public:
    Register regs[8];
    Program* program;
    LowLevelBlock* initial;
    bool isOverflow;

    LowLevelProgram(Program* wholeProgram);

    std::string generateAsm();
    LowLevelBlock* translateBlock(Block* block);
    void handleAssignment(Assignment* assign, std::vector<std::string>& translated);
    void handleWrite(Write* write, std::vector<std::string>& translated);
    void handleRead(Read* read, std::vector<std::string>& translated);
    void handleCond(Condition* cond, std::vector<std::string>& translated);
    void handleCall(Procedure_call* call, std::vector<std::string>& translated);

    //get variable into free register
    int getVal(Value* val,std::vector<std::string>& translated);

    //get var into "a"
    void getValIntoA(Value* val,std::vector<std::string>& translated);

    //puts var in a into free register, if value is index of array it stores this array in memory
    int putVal(Value* val,std::vector<std::string>& translated);

    //clear given register, store variable in memory
    void freeRegister(int num,std::vector<std::string>& translated);

    //put all variables into memory when calling procedures or jumping BBs or doing any operation that needs more regs like division
    void dumpRegs(std::vector<std::string>& translated);

    int getValFromString(std::string val,std::vector<std::string>& translated);

    //check if any array in registers is indexed as val, if yes store it 
    void valuePrecheck(Value* val, std::vector<std::string>& translated);

    //check if any array in registers is indexed as val, if remove from registers
    void valuePostcheck(Value* val, std::vector<std::string>& translated);

    void add(int reg, std::vector<std::string>& translated);

    void sub(int reg, std::vector<std::string>& translated);

    void mult(int reg, std::vector<std::string>& translated);

    void div(int reg, std::vector<std::string>& translated);

    void mod(int reg, std::vector<std::string>& translated);
};

#endif