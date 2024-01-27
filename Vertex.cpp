#include "./Vertex.hpp"
#include <iostream>
#include <vector>

///////////////////////////////////////////////
//INSTRUCTION
///////////////////////////////////////////////
std::vector<Identifier*> Instruction::getVars(){
    std::vector<Identifier*> empty;
    return empty;
}

std::vector<Instruction*> Instruction::getNext(){
    std::vector<Instruction*> nexts;
    nexts.push_back(next);
    return nexts;
}

Instruction::Instruction(){
    Instruction::next=nullptr;
}

bool Instruction::isCall(){
    return false;
}

std::string Instruction::print(){
    return "EMPTY INSTRUCTION\n";
}

bool Instruction::isConditional(){
    return false;
}

bool Instruction::isMerger(){
    return false;
}
///////////////////////////////////////////////
//MERGER
///////////////////////////////////////////////
std::string Merger::print(){
    std::string toRet="MERGER ";
    toRet.push_back(static_cast<char>(97+mergIndex));
    toRet+="\n";
    return toRet;
}


bool Merger::isMerger(){
    return true;
}
///////////////////////////////////////////////
//CONDITIONAL SIMPLE
///////////////////////////////////////////////
std::vector<Identifier*> ConditionalSimple::getVars(){
    std::vector<Identifier*> vars;
    //if value is a number, getVar returns empty string. Its strictly for semantic analisys
    if(cond->leftVal->getIdentifier()!=nullptr){
        if(dynamic_cast<Identifier*>(cond->leftVal)){
            vars.push_back(dynamic_cast<Identifier*>(cond->leftVal));
        }
    }
    if(cond->rightVal->getIdentifier()!=nullptr){
        if(dynamic_cast<Identifier*>(cond->rightVal)){
            vars.push_back(dynamic_cast<Identifier*>(cond->rightVal));
        }
    }
    return vars;
}

std::vector<Instruction*> ConditionalSimple::getNext(){
    std::vector<Instruction*> nexts;
    nexts.push_back(next);
    nexts.push_back(nextIfTrue);
    return nexts;
}

std::string ConditionalSimple::print(){
   return "CONDITION " + cond->leftVal->val + cond->operand + cond->rightVal->val+":\n";
}

bool ConditionalSimple::isConditional(){
    return true;
}
///////////////////////////////////////////////
//CONDITIONAL
///////////////////////////////////////////////
std::vector<Instruction*> Conditional::getNext(){
    std::vector<Instruction*> nexts;
    nexts.push_back(next);
    nexts.push_back(nextIfTrue);
    nexts.push_back(nextIfFalse);
    return nexts;
}

///////////////////////////////////////////////
//ASSIGNMENT
///////////////////////////////////////////////
std::vector<Identifier*> Assignment::getVars(){
    std::vector<Identifier*> vars;
    vars.push_back(identifier);
    if(expression->left->getIdentifier()!=nullptr){
        vars.push_back(expression->left->getIdentifier());
    }
    if(expression->right!=nullptr ){
        if(expression->right->getIdentifier()!=nullptr){
            vars.push_back(expression->right->getIdentifier());
        }
    }
    return vars;
}

std::string Assignment::print(){
    if(dynamic_cast<ExprComplex*>(expression)){
        ExprComplex* comp = dynamic_cast<ExprComplex*>(expression);
        return"ASSIGN "+identifier->val+" = "+comp->left->val+comp->operand+comp->right->val+"\n";
    }else{
        return"ASSIGN "+identifier->val+" = "+expression->left->val+"\n";
    }
}
///////////////////////////////////////////////
//PROCEDURE CALLL
///////////////////////////////////////////////
std::vector<Identifier*> Procedure_call::getVars(){
    //procedure calls are validated differently, so this returns empty vector
    std::vector<Identifier*> vars;
    for(int i=0;i<args->argsVec.size();i++){
        vars.push_back(args->argsVec[i]);
    }
    return vars;
}

bool Procedure_call::isCall(){
    return true;
}

std::string Procedure_call::print(){
    std::string toRet = "CALL "+name+" ";
    for(int i=0; i<args->argsVec.size();i++){
        toRet+=args->argsVec[i]->val+" ";
    }
    return toRet+"\n";
}

///////////////////////////////////////////////
//WRITE
///////////////////////////////////////////////
std::vector<Identifier*> Write::getVars(){
    std::vector<Identifier*> vars;
    if(val->getIdentifier()!=nullptr){
        vars.push_back(val->getIdentifier());
    }
    return vars;
}

std::string Write::print(){
    return "WRITE "+val->val+"\n";
}

///////////////////////////////////////////////
//READ
///////////////////////////////////////////////
std::vector<Identifier*> Read::getVars(){
    std::vector<Identifier*> vars;
    vars.push_back(ident);
    return vars;
}

std::string Read::print(){
    return "READ "+ident->val+"\n";
}

///////////////////////////////////////////////
//LINKED COMMANDS
///////////////////////////////////////////////
LinkedCommands::LinkedCommands(){
    LinkedCommands::head=nullptr;
    LinkedCommands::tail=nullptr;
}

void LinkedCommands::addInst(Instruction* inst){
    if(head!=nullptr){
        tail->next = inst;
        //std::cout<<"ADDING INST LIST:"<<inst->print();
        while(inst->next!=nullptr){
             //std::cout<<"WALKING THROUGHT INST LIST:"<<inst->print();
            inst = inst->next;
        }
        //std::cout<<"TAIL:"<<inst->print();
        tail = inst;
    }else{
        //std::cout<<"ADDING INST HEAD NULL:"<<inst->print();
        head = inst;
        while(inst->next!=nullptr){
             //std::cout<<"WALKING THROUGHT INST LIST:"<<inst->print();
            inst = inst->next;
        }
        //std::cout<<"TAIL:"<<inst->print();
        tail = inst;
    }
}

Instruction* LinkedCommands::getHead(){
    return this->LinkedCommands::head;
}

Instruction* LinkedCommands::getTail(){
    //std::cout<<"GETTING TAIL: "<<tail->print();
    return this->LinkedCommands::tail;
}

void LinkedCommands::setTail(Instruction* inst){
    while(tail->next!=nullptr){
        tail = tail->next;
    }
    tail -> next = inst;
    tail = inst;
    //std::cout<<"SETTING TAIL: "<<tail->print();
}

void LinkedCommands::setHead(Instruction* inst){
    inst->next = head;
    head = inst;
}

///////////////////////////////////////////////
//PROCEDURES ALL
///////////////////////////////////////////////
bool ProceduresAll::addProc(Procedure* proc){
    ProceduresAll::procedures.push_back(proc);
    return true;
}

void Program_part::toString(){
    std::cout<<"PROGRAM PART"<<std::endl;
}

void Main::toString(){
    std::cout<<"MAIN"<<std::endl;
}

void Procedure::toString(){
    std::cout<<"PROCEDURE "+head->name<<std::endl;
}