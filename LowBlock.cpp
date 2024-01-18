#include "LowBlock.hpp"

int ASCII_LOWER_A = 97;
////////////////////////////////////////////////////////////////
//
//Register
////////////////////////////////////////////////////////////////
Register::Register(){
    changed = false;
    locked = false;
    stored = nullptr;
}

void Register::freeRegister(){
    this->changed = false;
                 
    this->locked = false;
    this->stored = nullptr;
}

////////////////////////////////////////////////////////////////
//
//Architecture
////////////////////////////////////////////////////////////////
Architecture::Architecture(Program_part* part) : programPart(part) {
    for (int i = 0; i < 8; i++) {
        // Register* reg = new Register();
        // regs[i] = *reg;
        regs[i].index=i;
        regs[i].changed=false;
        regs[i].locked=false;
        regs[i].stored=nullptr;
    }
}

void Architecture::setBlock(LowLevelBlock* block){
    for(int i=0; i<8;i++){
        if(regs[i].changed){
            std::cout<<"\033[31;1;4mFAULT\033[0m REGISTER IS CHANGED\n";
        }
        if(regs[i].locked){
            std::cout<<"\033[31;1;4mFAULT\033[0m REGISTER IS LOCKED\n";
        }
    }
    currBlock = block;
}

void Architecture::forceClear(){
    for(int i=0; i<8;i++){
        regs[i].freeRegister();
    }
}

void Architecture::setCurrentPart(Program_part* part){
    for(int i=0; i<8;i++){
        if(regs[i].locked){
            std::cout<<"\033[31;1;4mFAULT\033[0m REGISTER IS LOCKED\n";
        }
    }
    programPart = part;
}

void Architecture::storeAll(){
    for(int i=1; i<6;i++){
        if(regs[i].changed){
            buildAddress(regs[i].stored, H);
            get(i);
            store(H);
            regs[i].changed=false;
        }
    }
}

void Architecture::storeReturn(){
    Procedure* proc = dynamic_cast<Procedure*>(programPart);
    for(int i=1;i<6;i++){
        Value* stored= regs[i].stored;
        if(proc->callableTable.find(stored->val)!=proc->callableTable.end()){
            if(regs[i].changed){
                buildAddress(regs[i].stored, H);
                get(i);
                store(H);
                regs[i].changed=false;
            }
        }
    }
}

void Architecture::clearAll(){
    for(int i=1;i<6;i++){
        if(regs[i].changed){
            std::cout<<"\033[31;1;4mFAULT\033[0m CLEARING REGISTER WITH CHANGED VALUES\n";
        }
        if(regs[i].locked){
            std::cout<<"\033[31;1;4mFAULT\033[0m CLEARING LOCKED REGISTER\n";
        }
        regs[i].freeRegister();
    }
    for(int i=0; i<garbageCollector.size();i++){
       // delete(garbageCollector[i]);
    }
}

void Architecture::dumpAll(){
    for(int i=0;i<8;i++){
        if(regs[i].changed){
            buildAddress(regs[i].stored, H);
            get(i);
            store(H);
        }
        if(regs[i].locked){
            std::cout<<"\033[31;1;4mFAULT\033[0m CLEARING LOCKED REGISTER\n";
        }
        regs[i].freeRegister();
    }

    for(int i=0; i<garbageCollector.size();i++){
        //delete(garbageCollector[i]);
    }
}

void Architecture::dumpUnlocked(){
    for(int i=0;i<8;i++){
        if(!regs[i].locked){
            if(regs[i].changed){
                buildAddress(regs[i].stored, H);
                get(i);
                store(H);
            }
            regs[i].freeRegister();
        }
    }
}

void Architecture::storePrecheck(Identifier* id){
    for(int i=1; i<6;i++){
        if(dynamic_cast<IndentifierArrPid*>(regs[i].stored)){
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(regs[i].stored);
            if(id->val==array->val&&regs[i].changed){
                buildAddress(regs[i].stored, H);
                get(i);
                store(H);
            }
        }
    }
}

void Architecture::storePostcheck(Identifier* id){
    for(int i=1; i<6;i++){
        if(dynamic_cast<IndentifierArrPid*>(regs[i].stored)){
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(regs[i].stored);
            if(id->val==array->val){
                regs[i].freeRegister();
            }
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
            regs[i].freeRegister();
            return i;
        }
    }
    for(int i=1;i<6;i++){
        if(!regs[i].locked){
            buildAddress(regs[i].stored, 7);
            get(i);
            store(H);
            return i;
        }
    }
    std::cout<<"\033[31;1;4mFAULT\033[0m ALL REGISTERS LOCKED\n";
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

int Architecture::putModifiedVal(Value* val){
    for(int i=1; i<6;i++){
        if(isSameVal(regs[i].stored, val)){
            regs[i].changed=true;
            put(i);
            return i;
        }
    }
    for(int i=1; i<6;i++){
        if(regs[i].stored==nullptr){
            regs[i].changed=true;
            regs[i].stored = val;
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
        if(procedure->callableTable.find(val->val)!=procedure->callableTable.end()){
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
    arch = new Architecture(whole->main);
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
            arch->regs[right].locked=false;
            if(comp->operand=="+"){
                arch->add(right);
            }else if(comp->operand=="-"){
                arch->sub(right);
            }

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
    arch->jump(call->name);
    arch->clearAll();;
}

void LowLevelProgram::handleReturn(){
    //if main just halt
    //if procedure store callable jump to return address
    if(dynamic_cast<Procedure*>(arch->programPart)){
        Procedure* proc = dynamic_cast<Procedure*>(arch->programPart);
        arch->returnMerger();
        arch->buildNum(proc->retAddr, A);
        arch->load(A);
        arch->inc(A);
        arch->inc(A);
        arch->jumpr(A);
    }else{
        arch->haltMain();
    }
}

LowLevelBlock* LowLevelProgram::generateLowBB(Block* block){
    if(block->visited){
        return mapBlock[block->index];
    }
    LowLevelBlock* lowBlock = new LowLevelBlock();
    arch->setBlock(lowBlock);
    bool isCond = false;
    for(int i=0;i<block->inst.size();i++){
        if(dynamic_cast<Assignment*>(block->inst[i])){
            handleAssign(dynamic_cast<Assignment*>(block->inst[i]));
        }else if(dynamic_cast<Read*>(block->inst[i])){
            handleRead(dynamic_cast<Read*>(block->inst[i]));
        }else if(dynamic_cast<Write*>(block->inst[i])){
            handleWrite(dynamic_cast<Write*>(block->inst[i]));
        }else if(dynamic_cast<Conditional*>(block->inst[i])){
            isCond=true;
            handleCond(dynamic_cast<Conditional*>(block->inst[i])->cond);
        }else if(dynamic_cast<Procedure_call*>(block->inst[i])){
            handleCall(dynamic_cast<Procedure_call*>(block->inst[i]));
        }
    }
    lowBlock->isCond = isCond;
    lowBlock->index = block->index;
    block->visited = true;
    mapBlock.insert(std::pair<int, LowLevelBlock*> (lowBlock->index, lowBlock));
    if(isCond){
        if(block->ifTrue==nullptr){
            handleReturn();
        }else{
            arch->dumpAll();
            lowBlock->next = generateLowBB(block->ifTrue);
        }
    }else{
        if(block->ifTrue==nullptr){
            handleReturn();
        }else{
            arch->dumpAll();
            lowBlock->next = generateLowBB(block->ifTrue);
        }
        if(block->ifFalse==nullptr){
            handleReturn();
        }else{
            arch->dumpAll();
            lowBlock->nextElse = generateLowBB(block->ifTrue);
        }
    }
    return lowBlock;
}

void LowLevelProgram::translate(){
    mainBlock = generateLowBB(program->BBs->initialBlock);
    arch->forceClear();
    for(int i=0;i<program->procedures->procedures.size();i++){
        std::string name = program->procedures->procedures[i]->head->name;
        arch->setCurrentPart(program->proceduresTable[name]);
        LowLevelBlock* procBlock = generateLowBB(program->BBs->procedureBBs[name]);
        proceduresBlock.insert(std::pair<std::string, LowLevelBlock*> (name, procBlock));
    }
}

