#include "./Block.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <thread>
#include <chrono>

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

void BlockRepresentation::DFStres(Instruction* current){
    current->visited=true;
    for(int i=0;i<current->getNext().size();i++){
        if(current->getNext()[i]!=nullptr){
        if(!current->getNext()[i]->visited){
            std::cout<<"->"<<current->getNext()[i]->print();
            DFStres(current->getNext()[i]);
        }else{
            std::cout<<current->print()<<"already visited->"<<current->getNext()[i]->print();
        }
        }
    }
}

void BlockRepresentation::DFSbis(Instruction* current){
    std::cout<<"\nNOW DFSING\n";
    std::stack<Instruction*> stack;
    stack.push(current);
    while(!stack.empty()){
        Instruction* top = stack.top();
        stack.pop();
        top->visited = false;
        std::cout<<top->print();
        for(int i=0;i<top->getNext().size();i++){
            if(top->getNext()[i]!=nullptr)
                if(top->getNext()[i]->visited){   
                    std::cout<<"->"<<top->getNext()[i]->print();
                    if(top->getNext()[i]->visited)
                        stack.push(top->getNext()[i]);
                }
                else{ 
                    std::cout<<top->print()<<"already visited->"<<top->getNext()[i]->print();
                    Instruction* next = top->getNext()[i];

                }
        }
    }  
    std::cout<<"END DFSING\n"; 
}

Block* BlockRepresentation::DFS(Instruction* inst){
    if(inst==nullptr){
        return nullptr;
    }
    while(inst->isMerger()){
        inst = inst->next;
        if(inst ==nullptr){
            return nullptr;
        }
    }
    if(blockMap.find(inst)!=blockMap.end()){
        return blockMap[inst];
    }
    Block* block = new Block();
    block->index = blockIndexes;
    blockIndexes++;
   // std::cout<<"INITIAL INSTRUCTION IN BLOCK: "<<inst->print();
    block->inst.push_back(inst);
    blockMap.insert(std::pair<Instruction*, Block*>(inst, block));
    while(!inst->isConditional()){
        inst = inst->next;
        if(inst==nullptr){
            return block;
        }else if(inst->isMerger()){
            break;
        }
       // std::cout<<inst->print();
        block->inst.push_back(inst);
    }
    if(inst->isConditional()){
        if(dynamic_cast<Conditional*>(inst)){
            Conditional* cond =  dynamic_cast<Conditional*>(inst);
            block->ifTrue = DFS(cond->nextIfTrue);
            block->ifFalse = DFS(cond->nextIfFalse);
            return block;
        }else{
            ConditionalSimple* simp = dynamic_cast<ConditionalSimple*> (inst);
            block->ifFalse = DFS(simp->next);
            block->ifTrue = DFS(simp->nextIfTrue);
            return block;
        }
    }
    if(inst->isMerger()){
        block->ifTrue=DFS(inst);
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

void BlockRepresentation::reset(){
    std::stack<Block*> stack;
    stack.push(initialBlock);
    while(!stack.empty()){
        Block* top = stack.top();
        stack.pop();
        if(top->visited){
            top->visited=false;
        }
        if(top->ifFalse!=nullptr&&top->ifFalse->visited){
            stack.push(top->ifFalse);
        }
        if(top->ifTrue!=nullptr&&top->ifTrue->visited){
            stack.push(top->ifTrue);
        }
    }
    for (auto pair : procedureBBs){
        stack.push(pair.second);
        while(!stack.empty()){
            Block* top = stack.top();
            stack.pop();
            if(top->visited){
                top->visited=false;
            }
            if(top->ifFalse!=nullptr&&top->ifFalse->visited){
                stack.push(top->ifFalse);
            }
            if(top->ifTrue!=nullptr&&top->ifTrue->visited){
                stack.push(top->ifTrue);
            }
        }
    }
}