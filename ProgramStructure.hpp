#ifndef PROGRAM_H
#define PROGRAM_H

#include "./Vertex.hpp"
#include "./Block.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Program{
private:
    Block* DFS(Instruction* current);
public: 
    std::map<std::string, Procedure*> proceduresTable; 
    ProceduresAll* procedures;
    Main* main;

    bool validateCallMain(Procedure_call* call);
    bool validateCallProc(Procedure_call* call, Procedure* current);
    bool semantic();
    void printer();
    Block* generadeBB();
};

#endif