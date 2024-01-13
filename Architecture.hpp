#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>
#include <map>
#include "./Types.hpp"
#include "./Block.hpp"

class Register{
public:
    int number;
    bool locked;
    Variable* stored;
};

class Cell{
public:
    unsigned long long adress;
    Variable* stored;
};

class Arch{
public:

};

#endif