#include "./Vertex.hpp"
#include <iostream>
#include <vector>

///////////////////////////////////////////////
//INSTRUCTION
///////////////////////////////////////////////
std::vector<Value*> Instruction::getVars(){
    std::vector<Value*> empty;
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

///////////////////////////////////////////////
//MERGER
///////////////////////////////////////////////
std::string Merger::print(){
    return "MERGER\n";
}

///////////////////////////////////////////////
//CONDITIONAL SIMPLE
///////////////////////////////////////////////
std::vector<Value*> ConditionalSimple::getVars(){
    std::vector<Value*> vars;
    //if value is a number, getVar returns empty string. Its strictly for semantic analisys
    if(cond->leftVal->getIdentifier()!=nullptr){
        vars.push_back(cond->leftVal);
    }
    if(cond->rightVal->getIdentifier()!=nullptr){
        vars.push_back(cond->rightVal);
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

std::string ConditionalSimple::print(){
   return "CONDITION " + cond->leftVal->val + cond->operand + cond->rightVal->val+":\n";
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

// std::string Conditional::print(){
//     return "IF "+cond->leftVal->val+ cond->operand+cond->rightVal->val+" ELSE: \n";
// }

///////////////////////////////////////////////
//CONDITIONAL WHILE
///////////////////////////////////////////////
// std::string ConditionalWhile::print(){
//     return "WHILE "+cond->leftVal->val+cond->operand+cond->rightVal->val+"DO \n";
// }

///////////////////////////////////////////////
//CONDITIONAL REPEAT
///////////////////////////////////////////////
// std::string ConditionalRepeat::print(){
//     return "REPEAT UNITL "+cond->leftVal->val+cond->operand+cond->rightVal->val+"DO \n";
// }

///////////////////////////////////////////////
//ASSIGNMENT
///////////////////////////////////////////////
std::vector<Value*> Assignment::getVars(){
    std::vector<Value*> vars;
    vars.push_back(identifier);
    //std::cout<<expression->left->getVar()<<std::endl;
    if(expression->left->getIdentifier()!=nullptr){
        vars.push_back(expression->left->getIdentifier());
    }
    if(expression->right!=nullptr ){
        /*not sure if i can do it `if(expression->right!=nullptr && expression->right->getVar()!="")`, if second condition would be checked
        too what would result in segmentation fault so I'll nest this condition*/
        if(expression->right->getIdentifier()!=nullptr){
            vars.push_back(expression->right->getIdentifier());
        }
    }
    return vars;
}

std::string Assignment::print(){
    if(dynamic_cast<ExprComplex*>(expression)){ //tu jest linijka 116
        ExprComplex* comp = dynamic_cast<ExprComplex*>(expression);
        return"ASSIGN "+identifier->val+" = "+comp->left->val+comp->operand+comp->right->val+"\n";
    }else{
        return"ASSIGN "+identifier->val+" = "+expression->left->val+"\n";
    }
}
///////////////////////////////////////////////
//PROCEDURE CALLL
///////////////////////////////////////////////
std::vector<Value*> Procedure_call::getVars(){
    //procedure calls are validated differently, so this returns empty vector
    std::vector<Value*> empty;
    return empty;
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
std::vector<Value*> Write::getVars(){
    std::vector<Value*> vars;
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
std::vector<Value*> Read::getVars(){
    std::vector<Value*> vars;
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

///////////////////////////////////////////////
//PROCEDURES ALL
///////////////////////////////////////////////
bool ProceduresAll::addProc(Procedure* proc){
    ProceduresAll::procedures.push_back(proc);
    return true;
}