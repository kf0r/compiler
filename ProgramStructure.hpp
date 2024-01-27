#ifndef PROGRAM_H
#define PROGRAM_H

#include "./Vertex.hpp"
#include "./Block.hpp"
#include <algorithm>
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
    bool valid = true;

    bool validateCallMain(Procedure_call* call);
    bool validateCallProc(Procedure_call* call, Procedure* current);
    static bool compareOffsets(Variable* a, Variable* b);
    bool checkOverflow(unsigned long long prevAddr, unsigned long long newAddr);
    void generateBB();
    void printBBs();


    void semanticBis();
    void procedureRedeclarations(); 
    void variableRedeclaration(Program_part* programPart);
    void DFS(Program_part* programPart);
    void reset(Program_part* programPart);
    void BFS(Program_part* part);
    void memoryManagement();
    void validateVariableUsage(Program_part* part, Identifier* identifier);
    void validateCall(Program_part* part, Procedure_call* call);
    void insertSymbol(Program_part* programPart, Identifier* id);

    void insertCall(Procedure* procedure, Identifier* id);
    
    void setInitialized(Program_part* part, Identifier* id);
    void setUsage(Program_part* part, Identifier* id);
    void checkInitialisations(Program_part* part, Identifier* id);
    void printAdresses();
};

#endif