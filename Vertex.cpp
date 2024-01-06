#include "./Vertex.hpp"
#include <iostream>
LinkedCommands::LinkedCommands(){
    LinkedCommands::head=nullptr;
    LinkedCommands::tail=nullptr;
}

void LinkedCommands::addInst(Instruction* inst){
    if(head!=nullptr){
        tail->next = inst;
        while(inst->next!=nullptr){
            inst = inst->next;
        }
        tail = inst;
    }else{
        head = inst;
        tail = head;
    }
}

Instruction* LinkedCommands::getHead(){
    return this->LinkedCommands::head;
}

Instruction* LinkedCommands::getTail(){
    return this->LinkedCommands::tail;
}


Instruction::Instruction(){
    Instruction::next=nullptr;
}

bool ProceduresAll::addProc(Procedure* proc){
    ProceduresAll::procedures.push_back(proc);
    return true;
}