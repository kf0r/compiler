#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include <map>
#include "./Types.hpp"
#include "./Vertex.hpp"
class Instruction;

class Block{
public:
    
    std::vector<Instruction*> inst;
    bool visited = false;
    Block* ifTrue;
    Block* ifFalse;
    int index;

    std::string toString();
};

class BlockRepresentation{
public:
    std::map<int, Block*> blockMap;
    Block* initialBlock;
    int blockIndexes=0;

    Block* DFS(Instruction* current);
    void setBB(Instruction* first);
    
    void print();
};

#endif