#include "./LowLevel.hpp"

//yep can be broken down to subprocedures but not now. Im in hurry, copy paste is faster.
LowLevelProgram::LowLevelProgram(Program* whole){
    int memAddr=0;
    program = whole;
    architecture = new Arch();
    
    for(auto pair : program->main->symbolTable){
        if(memAddr>MAX_MEM_SIZE||memAddr<0){
            isOverflow=true;
        }
        pair.second->adress = memAddr;
        memAddr++;
        memAddr+=pair.second->offset;
    }
    for(int i=0; i<program->procedures->procedures.size();i++){
        if(memAddr>MAX_MEM_SIZE||memAddr<0){
            isOverflow=true;
        }
        program->procedures->procedures[i]->retAddr = memAddr;
        for(auto pair : program->procedures->procedures[i]->symbolTable){
            if(memAddr>MAX_MEM_SIZE||memAddr<0){
                isOverflow=true;
            }
            pair.second->adress = memAddr;
            memAddr++;
            memAddr+=pair.second->offset;
        }
        for(auto pair : program->procedures->procedures[i]->callableTable){
            if(memAddr>MAX_MEM_SIZE||memAddr<0){
                isOverflow=true;
            }
            pair.second->adress = memAddr;
            memAddr++;
            memAddr+=pair.second->offset;
        }
    }
}

LowLevelBlock* LowLevelProgram::translateBlock(Block* block){
    std::vector<std::string> translated;
    for(int i=0; i<block->inst.size(); i++){
        Instruction* curr = block->inst[i];
        if(dynamic_cast<Assignment*>(curr)){
            handleAssignment(dynamic_cast<Assignment*>(curr), translated);
        }else if(dynamic_cast<Write*>(curr)){
            handleWrite(dynamic_cast<Write*>(curr), translated);
        }else if(dynamic_cast<Read*>(curr)){
            handleRead(dynamic_cast<Read*>(curr), translated);
        }else if(dynamic_cast<ConditionalSimple*>(curr)){
            handleCond(dynamic_cast<ConditionalSimple*>(curr)->cond, translated);
        }else if(dynamic_cast<Procedure_call*>(curr)){
            handleCall(dynamic_cast<Procedure_call*>(curr), translated);
        }
    }
}

void LowLevelProgram::handleAssignment(Assignment* assign, std::vector<std::string>& translated){

    if(dynamic_cast<ExprComplex*>(assign->expression)){
        ExprComplex* complex = dynamic_cast<ExprComplex*>(assign->expression);
        architecture->getVal(complex->right);
        architecture->getValIntoA(complex->left);
        

    }
}

void LowLevelProgram::handleWrite(Write* write, std::vector<std::string>& translated){
    //get val, write
}

void LowLevelProgram::handleRead(Read* read, std::vector<std::string>& translated){
    //read to free register
}

void LowLevelProgram::handleCond(Condition* cond, std::vector<std::string>& translated){
    //"a>b" -> a-b, JPOS true, JUMP false
    //"a>=b" -> b-a JZERO true, jump false
    //"a==b" a-b JPOS false b-a JZERO true JUMP false
    //"a!=b" a-b JPOS true b-a JPOS true JUMP false
}

void LowLevelProgram::handleCall(Procedure_call* call, std::vector<std::string>& translated){
    //dump regs
    //build address of given val, store in procedure memory, increase memory (((optimalisation)))
}

std::string LowLevelProgram::handleVal(Value* value){

}