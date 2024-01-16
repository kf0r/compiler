#ifndef PROGRAM_H
#define PROGRAM_H

#include "./Vertex.hpp"
#include "./Block.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>



class Program{
public: 
    std::map<std::string, Procedure*> proceduresTable; 
    ProceduresAll* procedures;
    Main* main;
    BlockRepresentation* BBs;

    bool validateCallMain(Procedure_call* call);
    bool validateCallProc(Procedure_call* call, Procedure* current);
    bool semantic();
    bool memoryManagement();
    bool checkInitialisations();
    bool checkUsage();
    bool setAdresses();
    static bool compareOffsets(Variable* a, Variable* b);
    bool checkOverflow(unsigned long long prevAddr, unsigned long long newAddr);
    void generateBB();
    void printBBs();

};

#endif