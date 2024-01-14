#include "./LowLevel.hpp"


///////////////////////////////////////////////
//LOW LEVEL PROGRAM
///////////////////////////////////////////////

//yep can be broken down to subprocedures but not now. Im in hurry, copy paste is faster.
LowLevelProgram::LowLevelProgram(Program* whole){
    for (int i=0; i<8; i++){
        regs[i].number = i;
        regs[i].index = static_cast<char>(ASCII_LOWER_A+i);
        regs[i].locked=false;
        regs[i].stored=nullptr;
        regs[i].indexStored ="";
    }

    int memAddr=0;
    program = whole;
    
    for(auto pair : program->main->symbolTable){
        if(memAddr>MAX_MEM_SIZE||memAddr<0){
            isOverflow=true;
        }
        pair.second->adress = memAddr;
        memAddr++;
        memAddr+=pair.second->offset;
    }
    for(int i=0; i<program->procedures->procedures.size();i++){
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
        if(memAddr>MAX_MEM_SIZE||memAddr<0){
            isOverflow=true;
        }
        program->procedures->procedures[i]->retAddr = memAddr;
        memAddr++;
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
    //storing into x[a] results in IMMEDIATE storage in memory
    //anything else isn't problematic so no problem :)
}

void LowLevelProgram::handleWrite(Write* write, std::vector<std::string>& translated){
}

void LowLevelProgram::handleRead(Read* read, std::vector<std::string>& translated){
}

void LowLevelProgram::handleCond(Condition* cond, std::vector<std::string>& translated){
}

void LowLevelProgram::handleCall(Procedure_call* call, std::vector<std::string>& translated){
    //dump regs
    //build address of given val, store in procedure memory, increase memory (((optimalisation)))
}

int LowLevelProgram::putVal(Value* val, std::vector<std::string>& translated){
}

//check it in the mornign, now im so exhausted that i dont know whats going on xD
int LowLevelProgram::getVal(Value* val, std::vector<std::string>& translated){

}

