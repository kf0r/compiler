#include "./Block.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stack>

std::string Block::toString(){
    std::string repr="";
    for(int i=0; i<inst.size(); i++){
        repr+=inst[i]->print();
    }
    return repr;
}


void BlockRepresentation::setBB(Instruction* initial){
    initialBlock = DFS(initial);
}

Block* BlockRepresentation::DFS(Instruction* current){
    //Block* block = new Block();
   // proceduresTable.insert(std::pair<std::string, Procedure*> (currentProcedure.head->name, &currentProcedure));
    if(current->blockIndex!=-1){
        return blockMap[current->blockIndex];
    }else{
        blockIndexes++;
                      
        Block* block = new Block();
        //block->inst.push_back(current);
        current->blockIndex = blockIndexes;
        while(current->getNext().size() == 1){
            block->inst.push_back(current);
            if(current->next==nullptr){
                return block;
            }else if(dynamic_cast<Merger*>(current->next)){
                while(dynamic_cast<Merger*>(current->next)){
                    current = current->next;
                    if(current==nullptr){
                        return block;
                    }
                }
                if(current!=nullptr){
                    block->ifTrue = DFS(current);
                }
                return block;
            }else{
                current = current->next;
            }
        }
        if(current->getNext().size() ==0){
            return block;
        }else{
            ConditionalSimple* conditionalSimple = dynamic_cast<ConditionalSimple*>(current);
            block->inst.push_back(current);
            if(dynamic_cast<Conditional*>(conditionalSimple)){
                Conditional* conditional = dynamic_cast<Conditional*>(conditionalSimple);
                block->ifFalse = DFS(conditional->nextIfFalse);
                block->ifTrue = DFS(conditional->nextIfTrue);
            }else{
                block->ifFalse = DFS(conditionalSimple->next);
                block->ifTrue = DFS(conditionalSimple->nextIfTrue);
            }
            return block;
        }
    }
}

void BlockRepresentation::print(){
    std::stack<Block*> stack;
    stack.push(initialBlock);
    while(!stack.empty()){
        Block* top = stack.top();
        stack.pop();
        if(!top->visited){
            std::cout<<top->toString();
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