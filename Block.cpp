#include "./Block.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stack>

std::string Block::toString(){
    std::string repr="B"+std::to_string(index)+"\n";
    for(int i=0; i<inst.size(); i++){
        repr+=inst[i]->print();
    }
    if(ifTrue!=nullptr){
    repr+"JUMP B"+std::to_string(ifTrue->index)+"\n";
    }
                                          
    if(ifFalse!=nullptr){
        repr+"ELSE JUMP B"+std::to_string(ifFalse->index)+"\n";
    }
    return repr+"";
}


void BlockRepresentation::setBB(Instruction* initial){
    initialBlock = DFS(initial);
}

void BlockRepresentation::addProcedureBB(Instruction* first, std::string name){
    procedureBBs.insert(std::pair<std::string, Block*>(name, DFS(first)));
}

Block* BlockRepresentation::DFS(Instruction* current){
    if(current==nullptr){
        return nullptr;
    }

    while(dynamic_cast<Merger*> (current)){
        current = current->next;
        if(current==nullptr){
            return nullptr;
        }
    }
    if(current->blockIndex!=-1){
        return blockMap[current->blockIndex];
    }
    Block* block = new Block();
    
    blockIndexes++;
    current->blockIndex = blockIndexes;
    block->index = blockIndexes;;
    blockMap.insert(std::pair<int, Block*>(blockIndexes, block));
    while(!dynamic_cast<Merger*> (current)&&!dynamic_cast<ConditionalSimple*>(current)){
        block->inst.push_back(current);
        current = current->next;
        if(current==nullptr){
            return block;
        }
    }
    if(dynamic_cast<Merger*> (current)){
        block->ifTrue = DFS(current);
    }else if(dynamic_cast<ConditionalSimple*> (current)){
        ConditionalSimple* simp = dynamic_cast<ConditionalSimple*> (current);
        block->inst.push_back(simp);
        if(dynamic_cast<Conditional*> (simp)){
            Conditional* cond = dynamic_cast<Conditional*> (simp);
            block->ifTrue = DFS(cond->nextIfTrue);
            block->ifFalse = DFS(cond->nextIfFalse);
        }else{
            block->ifTrue = DFS(simp->nextIfTrue);
            block->ifFalse = DFS(simp->next);
        }
    }
    return block;
}

void BlockRepresentation::print(Block* starting){
    std::stack<Block*> stack;
    stack.push(starting);
    while(!stack.empty()){
        Block* top = stack.top();
        stack.pop();
        if(!top->visited){
            std::cout<<top->toString();
            if(top->ifTrue!=nullptr){
                std::cout<<"TRUE JUMP B"<<top->ifTrue->index<<std::endl;
            }if(top->ifFalse!=nullptr){
                std::cout<<"FALSE JUMP B"<<top->ifFalse->index<<std::endl;
            }

            top->visited=true;
        }
        if(top->ifFalse!=nullptr&&!top->ifFalse->visited){
            stack.push(top->ifFalse);
        }
        if(top->ifTrue!=nullptr&&!top->ifTrue->visited){
            stack.push(top->ifTrue);
        }
    }
}