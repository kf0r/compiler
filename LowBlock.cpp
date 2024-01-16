#include "LowBlock.hpp"

int ASCII_LOWER_A = 97;
////////////////////////////////////////////////////////////////
//
//Register
////////////////////////////////////////////////////////////////
Register::Register(int i){
    index=i;
    name = "";
    name.push_back(static_cast<char>(ASCII_LOWER_A+i));
    changed = false;
    locked = false;
    stored = nullptr;
}

void Register::freeRegister(){
    changed = false;
    locked = false;
    stored = nullptr;
}

////////////////////////////////////////////////////////////////
//
//Architecture
////////////////////////////////////////////////////////////////
Architecture::Architecture(Program_part* part):regs{{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}}{
    programPart = part;
    for(int i=0;i<8;i++){
        regs[i] = Register(i);
    }
}

void Architecture::dumpAll(){
    for(int i=0;i<8;i++){
        if(regs[i].changed){
            buildAddress(regs[i].stored, H);
            get(i);
            store(H);
        }
        regs[i].freeRegister();
    }

    for(int i=0; i<garbageCollector.size();i++){
        delete(garbageCollector[i]);
    }
}

void Architecture::dumpUnlocked(){
    for(int i=0;i<8;i++){
        if(!regs[i].locked){
            if(regs[i].changed){
                buildAddress(regs[i].stored, 7);
                get(i);
                store(H);
            }
            regs[i].freeRegister();
        }
    }
}

int Architecture::getBestFree(){
    for(int i=1; i<6; i++){
        if(regs[i].stored!=nullptr){
            return i;
        }
    }
    for(int i=1;i<6;i++){
        if(!regs[i].locked&&!regs[i].changed){
            return i;
        }
    }
    for(int i=i;i<6;i++){
        if(!regs[i].locked){
            buildAddress(regs[i].stored, 7);
            get(i);
            store(H);
            return i;
        }
    }
    std::cout<<"\033[31;1;4mFAULT\033[0m ALL REGISTERS LOCKED";
    return -1;
}

int Architecture::getVal(Value* val){
    for(int i=1; i<6;i++){
        if(isSameVal(val, regs[i].stored)){
            return i;
        }
    }
    int bestIndex = getBestFree();
    getIntoA(val);

    put(bestIndex);
    return bestIndex;
}

void Architecture::getInto(int i, Value* val){
    if(isSameVal(val, regs[i].stored)){
        return;
    }
    if(!regs[i].changed||regs[i].stored==nullptr){
        regs[i].freeRegister();
    }else{
        buildAddress(regs[i].stored, H);
        get(i);
        store(H);
        regs[i].freeRegister();
    }
    //numbers can be builded directly into i, so can be optimised a bit
    getIntoA(val);
    put(i);
}

void Architecture::getIntoA(Value* val){
    for(int i=1;i<6;i++){
        if(isSameVal(val, regs[i].stored)){
            get(i);
            return;
        }
    }
    buildAddress(val,0);
    load(A);
    return;
}

bool Architecture::isSameVal(Value* first, Value* second){
    if((first==nullptr)!=(second==nullptr)){
        return false;
    }
    if(first->isArray()&&second->isArray()){
        if(dynamic_cast<IndentifierArrPid*>(first)&&dynamic_cast<IndentifierArrPid*>(second)){
            IndentifierArrPid* firstArr = dynamic_cast<IndentifierArrPid*>(first);
            IndentifierArrPid* secArr = dynamic_cast<IndentifierArrPid*>(second);
            return firstArr->val==secArr->val&&firstArr->address==secArr->address;
        }else if(dynamic_cast<IndentifierArrNumber*>(first)&&dynamic_cast<IndentifierArrNumber*>(second)){
            IndentifierArrNumber* firstArr = dynamic_cast<IndentifierArrNumber*>(first);
            IndentifierArrNumber* secArr = dynamic_cast<IndentifierArrNumber*>(second);
            return firstArr->val==secArr->val&&firstArr->address==secArr->address;
        }
        return false;
    }else if(!first->isArray()&&!second->isArray()){
        return first->val==second->val;
    }
    return false;
}

void Architecture::buildNum(unsigned long long number, int where){
////////////////////
}

int Architecture::putModifiedVal(Value* val){
    for(int i=1; i<6;i++){
        if(isSameVal(regs[i].stored, val)){
            regs[i].changed=true;
            put(i);
            return i;
        }
    }
    put(G);
    int best = getBestFree();
    regs[best].changed=true;
    regs[best].stored = val;
    get(G);
    put(best);
    return best;
}

void Architecture::buildAddress(Value* val, int where){
    if(dynamic_cast<IndentifierArrNumber*>(val)){
        if(isCallable(val)){
            IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
            Procedure* proc = dynamic_cast<Procedure*>(programPart);
            buildNum(proc->callableTable[array->val]->adress, 0);
            load(A);
            load(A);
            put(H);
            Number* number = new Number();
            garbageCollector.push_back(number);
            number->val = array->address;
            getIntoA(number);
            add(H);
            if(where!=A){
                put(where);
            }

            ////////////////////////////////////////
            //build addres in a, load twice, put e
            //get index into a
            //add
        }else{
            IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
            buildNum(programPart->symbolTable[array->val]->adress, 0);
            load(A);
            put(H);
            Number* number = new Number();
            garbageCollector.push_back(number);
            number->val = array->address;
            getIntoA(number);
            add(H);
            if(where!=A){
                put(where);
            }

            ////////////////////////////////////////
            //build addres in a, load once, put e
            //get index into a
            //add

        }
    }else if(dynamic_cast<IndentifierArrPid*>(val)){
        if(isCallable(val)){
            Procedure* proc = dynamic_cast<Procedure*>(programPart);
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(val);
            buildNum(proc->callableTable[array->val]->adress, 0);
            load(A);
            load(A);
            put(H);
            Identifier* id = new Identifier();
            garbageCollector.push_back(id);
            id->val = array->address;
            getIntoA(id);
            add(H);
            if(where!=A){
                put(H);
            }

            ////////////////////////////////////////
            //build addres in a, load twice, put e
            //get index into a
            //add
            //load a
        }else{
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(val);
            buildNum(programPart->symbolTable[array->val]->adress, 0);
            load(A);
            put(E);
            Identifier* id = new Identifier();
            garbageCollector.push_back(id);
            id->val = array->address;
            getIntoA(id);
            add(H);
            if(where!=A){
                put(where);
            }

            ////////////////////////////////////////
            //build addres in a, load once, put e
            //get index into a
            //add
            //load a
        }
    }else if(dynamic_cast<Identifier*>(val)){
        if(isCallable(val)){
            Procedure* proc = dynamic_cast<Procedure*>(programPart);
            buildNum(proc->callableTable[val->val]->adress, 0);
            load(A);
            if(where!=A){
                put(where);
            }

            ////////////////////////////////////////
            //build addres in a, load 
        }else{
            buildNum(programPart->symbolTable[val->val]->adress, where);

            ////////////////////////////////////////
            //build addres in a
        }
    }else if(dynamic_cast<Number*>(val)){
        buildNum(std::stoull(val->val), where);
    }
}

bool Architecture::isCallable(Value* val){
    if(dynamic_cast<Main*>(programPart)){
        //we are in main, variables aren't callable
        return false;
    }else{
        Procedure* procedure = dynamic_cast<Procedure*>(programPart);
        if(procedure->callableTable[val->val]){
            return true;
        }
        return false;
    }
}

////////////////////////////////////////////////////////////////
//
//LowLevelProgram
////////////////////////////////////////////////////////////////

LowLevelProgram::LowLevelProgram(Program* whole){
    program = whole;
    Architecture* arch = new Architecture(whole->main);
}

//if we assign a=b-c we have to check for x[a] in registers
void LowLevelProgram::handleAssign(Assignment* assing){
    Expression* expression = assing->expression;
    arch->storePrecheck(assing->identifier);
    if(dynamic_cast<ExprComplex*>(expression)){
        ExprComplex* comp = dynamic_cast<ExprComplex*>(expression);
        if(comp->operand=="+"||comp->operand=="-"){

            int right = arch->getVal(comp->right);
            arch->regs[right].locked=true;
            arch->getIntoA(comp->left);

            if(comp->operand=="+"){
                arch->add(right);
            }else if(comp->operand=="-"){
                arch->sub(right);
            }

            arch->regs[right].locked=false;

        }else if(comp->operand=="/"||comp->operand=="%"||comp->operand=="*"){

            arch->getInto(C, comp->right);
            arch->regs[C].locked = true;
            arch->getInto(B, comp->left);
            arch->regs[C].locked = false;

            arch->storeAll();
            if(comp->operand=="/"){
                arch->div();
            }else if(comp->operand=="%"){
                arch->mod();
            }else if(comp->operand=="*"){
                arch->mult();
            }
            arch->clearAll();
        }

        //we left some omptimisation possibiliteis like check if we can multiply by bitshifting etc

    }else{
        arch->getIntoA(expression->left);
    }
    arch->putModifiedVal(assing->identifier);
    arch->storePostcheck(assing->identifier);
}

void LowLevelProgram::handleRead(Read* read){
    arch->storePrecheck(read->ident);
    arch->read();
    arch->putModifiedVal(read->ident);
    arch->storePostcheck(read->ident);
}

void LowLevelProgram::handleWrite(Write* write){
    arch->getIntoA(write->val);
    arch->write();
}

void LowLevelProgram::handleCond(Condition* cond){
    //store all changed without dumping
    arch->storeAll();
    Value* left = cond->leftVal;
    Value* right = cond->rightVal;
    if(cond->operand==">"){

        int rightReg = arch->getVal(right);
        arch->getIntoA(left);
        arch->sub(rightReg);

        arch->jpos(true);
        arch->jzero(false);

    }else if(cond->operand=="<"){

        int leftReg = arch->getVal(left);
        arch->getIntoA(right);
        arch->sub(leftReg);

        arch->jpos(true);
        arch->jzero(false);

    }else if(cond->operand==">="){

        int leftReg = arch->getVal(left);
        arch->getIntoA(right);
        arch->sub(leftReg);

        arch->jpos(false);
        arch->jzero(true);

    }else if(cond->operand=="<="){

        int rightReg = arch->getVal(right);
        arch->getIntoA(left);
        arch->sub(rightReg);

        arch->jpos(false);
        arch->jzero(true);

    }else if(cond->operand=="!="){
        int rightReg = arch->getVal(right);
        arch->regs[rightReg].locked = true;

        int leftReg = arch->getVal(left);
        arch->regs[rightReg].locked = false;
        arch->get(leftReg);
        arch->sub(rightReg);
        arch->jpos(true);

        arch->get(rightReg);
        arch->sub(leftReg);
        arch->jpos(true);
        arch->jzero(false);

    }else if(cond->operand=="=="){
        int rightReg = arch->getVal(right);
        arch->regs[rightReg].locked = true;

        int leftReg = arch->getVal(left);
        arch->regs[rightReg].locked = false;
        arch->get(leftReg);
        arch->sub(rightReg);
        arch->jpos(false);

        arch->get(rightReg);
        arch->sub(leftReg);
        arch->jpos(false);
        arch->jzero(true);
    }
    arch->clearAll();
}

void LowLevelProgram::handleCall(Procedure_call* call){
    //store all changed without dumping
    //build initial address in "f", build each address in a, store, increment f, strk a, store f, jump to procedure address. 
    //free all regs (no storing)
    arch->storeAll();
    Procedure* proc = program->proceduresTable[call->name];
    unsigned long long initial = proc->initialAddr;
    arch->buildNum(initial, G);

    for(int i=0;i<call->args->argsVec.size();i++){
        arch->buildAddress(call->args->argsVec[i], A);
        arch->store(G);
        arch->inc(G);
    }
    arch->strk(A);
    arch->store(G);

    /////////////////////// JUMP TO PROCEDURE SOMEHOW
    arch->jump();
    arch->clearAll();;
}

void LowLevelProgram::handleReturn(){
    //if main just halt
    //if procedure store callable jump to return address
    if(dynamic_cast<Procedure*>(arch->programPart)){
        Procedure* proc = dynamic_cast<Procedure*>(arch->programPart);
        arch->storeReturn();
        arch->buildNum(proc->retAddr, A);
        arch->load(A);
        arch->inc(A);
        arch->inc(A);
        arch->jumpr(A);
    }else{
        arch->halt();
    }
}