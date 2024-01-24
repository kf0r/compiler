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
    void commonSubexpression();
    void optimiseConditions();
    void removeUnreachable();
    void simplifyAlgebraic();
    void pruneUnreachable();
};

class BlockRepresentation{
public:
    std::map<Instruction*, Block*> blockMap;
    Block* initialBlock;
    std::map<std::string, Block*> procedureBBs;
    int blockIndexes=0;

    Block* DFS(Instruction* current);
    void setBB(Instruction* first);
    void addProcedureBB(Instruction* first, std::string name);
    void print(Block* starting);
    void reset();
    void DFSbis(Instruction* inst);
    void DFStres(Instruction* current);
};

#endif