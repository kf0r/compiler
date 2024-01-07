#include "./Vertex.hpp"
#include <iostream>
#include <vector>

std::vector<std::string> Instruction::getVars(){
    std::vector<std::string> empty;
    return empty;
}

std::vector<Instruction*> Instruction::getNext(){
    std::vector<Instruction*> nexts;
    nexts.push_back(next);
    return nexts;
}

std::vector<std::string> ConditionalSimple::getVars(){
    std::vector<std::string> vars;
    //if value is a number, getVar returns empty string. Its strictly for semantic analisys
    if(cond->leftVal->getVar()!=""){
        vars.push_back(cond->leftVal->getVar());
    }
    if(cond->rightVal->getVar()!=""){
        vars.push_back(cond->rightVal->getVar());
    }
    
    return vars;
}
//yep i could do some makro but in my philosphy its more readable :P

std::vector<Instruction*> ConditionalSimple::getNext(){
    std::vector<Instruction*> nexts;
    nexts.push_back(next);
    nexts.push_back(nextIfTrue);
    return nexts;
}

std::vector<Instruction*> Conditional::getNext(){
    std::vector<Instruction*> nexts;
    nexts.push_back(next);
    nexts.push_back(nextIfTrue);
    nexts.push_back(nextIfFalse);
    return nexts;
}


std::vector<std::string> Assignment::getVars(){
    std::vector<std::string> vars;
    if(identifier->getVar()!=""){
        vars.push_back(identifier->getVar());
    }
    //std::cout<<expression->left->getVar()<<std::endl;
    if(expression->left->getVar()!=""){
        vars.push_back(expression->left->getVar());
    }
    if(expression->right!=nullptr ){
        /*not sure if i can do it `if(expression->right!=nullptr && expression->right->getVar()!="")`, if second condition would be checked
        too what would result in segmentation fault so I'll nest this condition*/
        if(expression->right->getVar()!=""){
            vars.push_back(expression->right->getVar());
        }
    }
    return vars;
}

std::vector<std::string> Procedure_call::getVars(){
    std::vector<std::string> vars;
    for(int i=0; i<args->argsVec.size(); i++){
        //provided grammar says that arguments for function are variables
        vars.push_back(args->argsVec[i]->val);
    }
    return vars;
}

std::vector<std::string> Write::getVars(){
    std::vector<std::string> vars;
    if(val->getVar()!=""){
        vars.push_back(val->getVar());
    }
    return vars;
}

std::vector<std::string> Read::getVars(){
    std::vector<std::string> vars;
    vars.push_back(ident->val);
    return vars;
}


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