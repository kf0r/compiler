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
    if(dynamic_cast<ExprComplex*>(assign->expression)){
        ExprComplex* complex = dynamic_cast<ExprComplex*>(assign->expression);
        int rightReg = getVal(complex->right,translated);
        getValIntoA(complex->left,translated);
        std::string operation = "";
        //yep it might not be elegant but its for studies, not some corporational production code xd
        if(complex->operand=="+"){
            operation = "ADD "+static_cast<char>(rightReg+ASCII_LOWER_A);
        }else if(complex->operand=="-"){
            operation = "SUB "+static_cast<char>(rightReg+ASCII_LOWER_A);
        }else if(complex->operand=="/"){
            //dump regs
            operation = "DIV "+static_cast<char>(rightReg+ASCII_LOWER_A);
        }else if(complex->operand=="*"){
            //free some regs
            operation = "MULT "+static_cast<char>(rightReg+ASCII_LOWER_A);
        }else if(complex->operand=="%"){
            //dump regs
            operation = "MOD "+static_cast<char>(rightReg+ASCII_LOWER_A);
        }
        translated.push_back(operation);
    }else{
        getValIntoA(assign->expression->left, translated);
    }
    regs[putVal(assign->identifier, translated)].changed=true;
}

void LowLevelProgram::handleWrite(Write* write, std::vector<std::string>& translated){
    getValIntoA(write->val, translated);
    translated.push_back("WRITE");
}

void LowLevelProgram::handleRead(Read* read, std::vector<std::string>& translated){
    translated.push_back("READ");
    putVal(read->ident, translated);
}

void LowLevelProgram::handleCond(Condition* cond, std::vector<std::string>& translated){
    //"a>b" -> a-b, JPOS true, JUMP false
    //"a>=b" -> b-a JZERO true, jump false
    //"a==b" a-b JPOS false b-a JZERO true JUMP false
    //"a!=b" a-b JPOS true b-a JPOS true JUMP false
    //yep not elegant. Who asked?
    //TODO: ADD LOCKS FOR REGISTERS WITH VARIABLES AND UNLOCKS
    if(cond->operand==">"){
        int right = getVal(cond->rightVal, translated);
        getValIntoA(cond->leftVal, translated);
        std::string op = "SUB "+static_cast<char>(right+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JPOS true");
        translated.push_back("JZERO false");
    }else if(cond->operand=="<"){
        int left = getVal(cond->leftVal, translated);
        getValIntoA(cond->rightVal, translated);
        std::string op = "SUB "+static_cast<char>(left+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JPOS true");
        translated.push_back("JZERO false");
    }else if(cond->operand==">="){
        int left = getVal(cond->leftVal, translated);
        getValIntoA(cond->rightVal, translated);
        std::string op = "SUB "+static_cast<char>(left+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JZERO true");
        translated.push_back("JPOS false");
    }else if(cond->operand=="<="){
        int right = getVal(cond->rightVal, translated);
        getValIntoA(cond->leftVal, translated);
        std::string op = "SUB "+static_cast<char>(right+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JZERO true");
        translated.push_back("JPOS false");
    }else if(cond->operand=="=="){
        int right = getVal(cond->rightVal, translated);
        int left = getVal(cond->leftVal, translated);
        getValIntoA(cond->leftVal, translated);
        std::string op = "SUB "+static_cast<char>(right+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JPOS false");
        getValIntoA(cond->rightVal, translated);
        op = "SUB "+static_cast<char>(left+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JPOS false");
        translated.push_back("JUMP true");
    }else if(cond->operand=="!="){
        int right = getVal(cond->rightVal, translated);
        int left = getVal(cond->leftVal, translated);
        getValIntoA(cond->leftVal, translated);
        std::string op = "SUB "+static_cast<char>(right+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JPOS true");
        getValIntoA(cond->rightVal, translated);
        op = "SUB "+static_cast<char>(left+ASCII_LOWER_A);
        translated.push_back(op);
        translated.push_back("JPOS true");
        translated.push_back("JUMP false");
    }
}

void LowLevelProgram::handleCall(Procedure_call* call, std::vector<std::string>& translated){
    //dump regs
    //build address of given val, store in procedure memory, increase memory (((optimalisation)))
}

int LowLevelProgram::putVal(Value* val, std::vector<std::string>& translated){
    if(dynamic_cast<Number*>(val)){
        //if we store number thats already stored, we do nothing, return index of register
        for(int i=1; i<7;i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==val->val){
                    return i;
                }
            }
        }
        //else we put this into free register
        for(int i=1; i<7;i++){
            if(regs[i].stored==nullptr){
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                regs[i].stored = val;
                return i;
            }
        }
        //if theres no free register, we free unlocked and store it there
        for(int i=1; i<7;i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                regs[i].stored = val;
                return i;
            }
        }
    }else if(dynamic_cast<IndentifierArrNumber*>(val)){

    }else if(dynamic_cast<IndentifierArrPid*>(val)){

    }else if(dynamic_cast<Identifier*>(val)){
        //we are changing variable. We should check if it wasnt index of any array in registers
        bool wasAddres = false;
        int adress = 0;
        for(int i=1; i<7;i++){
            if(regs[i].indexStored==val->val){
                wasAddres==true;
                adress=i;
                break;
            }
        }

    }
}

//check it in the mornign, now im so exhausted that i dont know whats going on xD
int LowLevelProgram::getVal(Value* val, std::vector<std::string>& translated){
    if(dynamic_cast<Number*>(val)){
        //a is special, e is for building addresses and values
        for(int i=1; i<7; i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==val->val){
                    return i;
                }
            }
        }
        //no reg is equal, so we look for empty register to store value
        for(int i=1;i<7;i++){
            if(regs[i].stored==nullptr){
                translated.push_back("BUILD "+val->val);
                translated.push_back("GET e");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=val;
                return i;
            }
        }
        //no free register? look for unlocked register, free it and store value
        for(int i=1;i<7;i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                translated.push_back("BUILD "+val->val);
                translated.push_back("GET e");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=val;
                return i;
            }
        }
    }else if(dynamic_cast<IndentifierArrNumber*>(val)){
        IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
        for(int i=1; i<7; i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==array->val&&regs[i].indexStored==array->address){
                    return i;
                }
            }
        }
        for(int i=1;i<7;i++){
            if(regs[i].stored==nullptr){
                translated.push_back("BUILD "+std::to_string(program->main->symbolTable[array->val]->adress+stoull(array->address)));
                translated.push_back("LOAD e");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=array;
                regs[i].indexStored = array->address;
                return i;
            }
        }
        for(int i=1;i<7;i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                translated.push_back("BUILD "+std::to_string(program->main->symbolTable[array->val]->adress+stoull(array->address)));
                translated.push_back("LOAD e");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=array;
                regs[i].indexStored = array->address;
                return i;
            }
        }
    }else if(dynamic_cast<IndentifierArrPid*>(val)){
        //arr[a], when we are putting new a in register, we also free arr[a], so if we find arr[a] we can safely take it from register
        IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(val);
        for(int i=1; i<7; i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==array->val&&regs[i].indexStored==array->address){
                    return i;
                }
            }
        }
        //unfortunately theres no arr[a] :(((
        int registerWithIndex=getValFromString(array->address, translated);
        regs[registerWithIndex].locked=true;
        for(int i=1;i<7;i++){
            if(regs[i].stored==nullptr){
                translated.push_back("BUILD "+std::to_string(program->main->symbolTable[array->val]->adress+stoull(array->address)));
                translated.push_back("GET e");
                std::string op = "ADD ";
                op.push_back(static_cast<char>(ASCII_LOWER_A+registerWithIndex));
                translated.push_back(op);
                translated.push_back("LOAD a");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=array;
                regs[i].indexStored = array->address;
                return i;
            }
        }
        for(int i=1;i<7;i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                translated.push_back("BUILD "+std::to_string(program->main->symbolTable[array->val]->adress+stoull(array->address)));
                translated.push_back("GET e");
                std::string op = "ADD ";
                op.push_back(static_cast<char>(ASCII_LOWER_A+registerWithIndex));
                translated.push_back(op);
                translated.push_back("LOAD a");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=array;
                regs[i].indexStored = array->address;
                return i;
            }
        }
    }else if(dynamic_cast<Identifier*>(val)){
        for(int i=1;i<7;i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==val->val){
                    return i;
                }
            }
        }

        for(int i=1;i<7;i++){
            if(regs[i].stored==nullptr){
                translated.push_back("BUILD "+std::to_string(program->main->symbolTable[val->val]->adress));
                translated.push_back("LOAD e");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=val;
                return i;
            }
        }

        for(int i=1; i<7;i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                translated.push_back("BUILD "+std::to_string(program->main->symbolTable[val->val]->adress));
                translated.push_back("LOAD e");
                std::string op = "PUT "+static_cast<char>(i+ASCII_LOWER_A);
                translated.push_back(op);
                regs[i].stored=val;
                return i;
            }
        }
    }
}

