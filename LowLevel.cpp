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
    valuePrecheck(assign->identifier, translated);
    //anything else isn't problematic so no problem :)
    if(dynamic_cast<ExprComplex*>(assign->expression)){
        ExprComplex* complex =  dynamic_cast<ExprComplex*>(assign->expression);
        int rightSide = getVal(complex->right, translated);
        regs[rightSide].locked = true;
        getValIntoA(complex->left, translated);
        regs[rightSide].locked = false;
        if(complex->operand=="+"){
            add(rightSide, translated);
        }else if(complex->operand=="-"){
            sub(rightSide, translated);
        }else if(complex->operand=="*"){
            mult(rightSide, translated);
        }else if(complex->operand=="/"){
            div(rightSide, translated);
        }else if(complex->operand=="%"){
            mod(rightSide, translated);
        }
        putVal(assign->identifier, translated);
    }else if(dynamic_cast<ExprSimple*>(assign->expression)){
        ExprSimple* simp = dynamic_cast<ExprSimple*>(assign->expression);
        getValIntoA(simp->left, translated);
        putVal(assign->identifier, translated);
    }
    valuePostcheck(assign->identifier, translated);
}

void LowLevelProgram::handleWrite(Write* write, std::vector<std::string>& translated){
    getValIntoA(write->val, translated);
    //can be further optimised to put val back into registers, but now it'll do
    translated.push_back("WRITE");
}

void LowLevelProgram::handleRead(Read* read, std::vector<std::string>& translated){
    valuePrecheck(read->ident, translated);
    translated.push_back("READ");
    putVal(read->ident, translated);
    valuePostcheck(read->ident, translated);
}

///////////////////////////////////////////////////////
//////////a>b -> a-b -> JPOS true JUMP false///////////
//////////a>=b -> b-a -> JZERO true JUMP false/////////
//a==b -> a-b -> JPOS false b-a JZERO true JUMP false//
///////////////////////////////////////////////////////
void LowLevelProgram::handleCond(Condition* cond, std::vector<std::string>& translated){
    if(cond->operand==">"){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        getValIntoA(cond->leftVal, translated);
        regs[right].locked = false;
        sub(right, translated);
        translated.push_back("JPOS true");
        translated.push_back("JUMP false");
    }else if(cond->operand==">="){
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->rightVal, translated);
        regs[left].locked = false;
        sub(left, translated);
        translated.push_back("JZERO true");
        translated.push_back("JUMP false");
    }else if(cond->operand=="=="){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->leftVal, translated);
        sub(right, translated);
        translated.push_back("JPOS false");
        getValIntoA(cond->rightVal, translated);
        sub(left, translated);
        translated.push_back("JPOS false");
        translated.push_back("JUMP true");
        regs[left].locked = false;
        regs[right].locked = false;
    }else if(cond->operand=="!="){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->leftVal, translated);
        sub(right, translated);
        translated.push_back("JPOS true");
        getValIntoA(cond->rightVal, translated);
        sub(left, translated);
        translated.push_back("JPOS true");
        translated.push_back("JUMP false");
        regs[left].locked = false;
        regs[right].locked = false;
    }else if(cond->operand=="<"){
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->rightVal, translated);
        regs[left].locked = false;
        sub(left, translated);
        translated.push_back("JPOS true");
        translated.push_back("JUMP false");
    }else if(cond->operand=="<="){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        getValIntoA(cond->leftVal, translated);
        regs[right].locked = false;
        sub(right, translated);
        translated.push_back("JZERO true");
        translated.push_back("JUMP false");
    }
}

void LowLevelProgram::handleCall(Procedure_call* call, std::vector<std::string>& translated){
    //dump regs
    //build address of given val, store in procedure memory, increase memory (((optimalisation)))
}

int LowLevelProgram::putVal(Value* val, std::vector<std::string>& translated){
    //set changed to true in register, so always when dumping we should store it
}

//check it in the mornign, now im so exhausted that i dont know whats going on xD
int LowLevelProgram::getVal(Value* val, std::vector<std::string>& translated){
    
}

void LowLevelProgram::getValIntoA(Value* val, std::vector<std::string>& translated){

}
