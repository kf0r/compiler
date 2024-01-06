#ifndef PROGRAM_H
#define PROGRAM_H

#include "./Vertex.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Program{
public: 
    std::map<std::string, Procedure*> proceduresTable; 
    ProceduresAll* procedures;
    Main* main;
    bool semantic();
};

#endif