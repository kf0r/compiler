#ifndef ARCH_H
#define ARCH_H

#include <vector>
#include <string>
#include <map>
#include "./Types.hpp"
#include "./Block.hpp"

const int ASCII_LOWER_A = 97;

class Register{
public:
    int number;
    char index;

    //lock during operations, so architecture wouldnt free register thats currently in use
    bool locked;
    Variable* stored;
    Identifier* identifier;
    Value* val;
};  

class Arch{
public:
    Register regs[8];

    Arch();
    //get variable into free register
    std::string getVar(Identifier* ident);

    //clear given register
    std::string freeRegister(int num);

    //put all variables into memory when calling procedures or jumping BBs or doing any operation that needs more regs like division
    std::string dumpRegs();
};

#endif