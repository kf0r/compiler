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

// Block* BlockRepresentation::DFS(Instruction* current){
//     if(current==nullptr){
//         return nullptr;
//     }
//     std::cout<<current->print();
//     while(current->isMerger()){
//         //std::cout<<current->index<<std::endl;
//         std::cout<<"MERGER: "<<current->print()<<std::endl;
//         current = current->next;
//         if(current==nullptr){
//             return nullptr;
//         }
//     }
//    // std::cout<<current->index<<std::endl;
//     if(blockMap.find(current)!=blockMap.end()){
//         std::cout<<"IN BLOCK ALREADY: "<<blockMap[current]->inst[0]->print()<<std::endl;
//         return blockMap[current];
//     }else{
//         std::cout<<"NEW INST: "<<current->print()<<std::endl;
//     }

//     Block* block = new Block();
    
//     blockIndexes++;
//     current->blockIndex = blockIndexes;
//     block->index = blockIndexes;
//     std::cout<<current->print();
//     blockMap.insert(std::pair<Instruction*, Block*>(current, block));

//     while(!current->isMerger()&&!current->isConditional()){
//         block->inst.push_back(current);
//         current = current->next;
//         if(current==nullptr){
//             return block;
//         }
//     }
//     if(dynamic_cast<Merger*> (current)){
//         block->ifTrue = DFS(current->next);
//         //std::cout<<"NEW: "<<blockMap[current]->inst[0]->print()<<std::endl;
//     }else if(dynamic_cast<ConditionalSimple*> (current)){
//         ConditionalSimple* simp = dynamic_cast<ConditionalSimple*> (current);
//         block->inst.push_back(simp);
//         if(dynamic_cast<Conditional*> (simp)){
//             Conditional* cond = dynamic_cast<Conditional*> (simp);
//             block->ifTrue = DFS(cond->nextIfTrue);
//             block->ifFalse = DFS(cond->nextIfFalse);
//         }else{
//             block->ifTrue = DFS(simp->nextIfTrue);
//             block->ifFalse = DFS(simp->next);
//         }
//     }
//     return block;
// }

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
                    //std::cout<<"ALREADY VISITED: "<<top->getNext()[i]->print();
                    Instruction* next = top->getNext()[i];

                    //std::cout<<"IT WAS POINTNG TO: "<<next->print();
                }
        }
    }  
    std::cout<<"END DFSING\n"; 
}

Block* BlockRepresentation::DFS(Instruction* inst){
    if(inst==nullptr){
        std::cout<<"INSTRUCTION WAS NULLPTR\n";
        return nullptr;
    }
    while(inst->isMerger()){
        inst = inst->next;
        if(inst ==nullptr){
            return nullptr;
        }
    }
    if(blockMap.find(inst)!=blockMap.end()){
        std::cout<<"ALREADY IN"<<inst->print();
        return blockMap[inst];
    }
    Block* block = new Block();
    block->index = blockIndexes;
    blockIndexes++;
    std::cout<<"INITIAL INSTRUCTION IN BLOCK: "<<inst->print();
    block->inst.push_back(inst);
    blockMap.insert(std::pair<Instruction*, Block*>(inst, block));
    while(!inst->isConditional()){
        inst = inst->next;
        if(inst==nullptr){
            return block;
        }else if(inst->isMerger()){
            break;
        }
        std::cout<<inst->print();
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