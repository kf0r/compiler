#ifndef PROGRAM_H
#define PROGRAM_H

#include "./Vertex.hpp"
#include <iostream>
#include <string>
#include <vector>

class Program{
public:
    ProceduresAll* procedures;
    Main* main;
    bool semantic();
};

#endif