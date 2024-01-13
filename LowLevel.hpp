#ifndef LOW_H
#define LOW_H
#include <vector>
#include <string>
#include "./Block.hpp"
#include "./Architecture.hpp"
#include "./Vertex.hpp"
#include "./ProgramStructure.hpp"

unsigned long long MAX_MEM_SIZE = 4611686018427388000;

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
    Program* program;
    LowLevelBlock* initial;
    Arch* architecture;
    bool isOverflow;

    LowLevelProgram(Program* wholeProgram);

    std::string generateAsm();
    LowLevelBlock* translateBlock(Block* block);
    void handleAssignment(Assignment* assign, std::vector<std::string>& translated);
    void handleWrite(Write* write, std::vector<std::string>& translated);
    void handleRead(Read* read, std::vector<std::string>& translated);
    void handleCond(Condition* cond, std::vector<std::string>& translated);
    void handleCall(Procedure_call* call, std::vector<std::string>& translated);
    std::string handleVal(Value* value);
};

#endif