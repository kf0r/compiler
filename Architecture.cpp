#include "LowBlock.hpp"

int ASCII_a = 97;
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
//LowBlocks
////////////////////////////////////////////////////////////////
std::string LowInstruction::toString(){
    return inst;
}

std::string ReturnMerger::toString(){
    return "MERGER (it shouldnt be visible)";
}

std::string Jumper::toString(){
    std::string toRet = inst+std::to_string(jumpTo->index);
    return toRet;
}

int Jumper::test(){
    return 1;
}
int Jump::test(){
    return 2;
}
int JPos::test(){
    return 3;
}
int JZero::test(){
    return 4;
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
    counter = 0;
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

void Architecture::clearExplicit(int reg){
    if(regs[reg].changed){
        buildAddress(regs[reg].stored, H);
        get(reg);
        store(H);
    }
    regs[reg].freeRegister();
}

void Architecture::clearAll(){
    for(int i=1;i<6;i++){
        if(regs[i].changed){
            std::cout<<"\033[31;1;4mFAULT\033[0m CLEARING REGISTER WITH CHANGED VALUES: "<<regs[i].stored->val<<"\n";
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
            std::cout<<"\033[31;1;4mFAULT\033[0m DUMPING LOCKED REGISTER\n";
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
        std::cout<<"Reg "<<static_cast<char>(97+i)<<" is free\n";
        if(regs[i].stored!=nullptr){
            return i;
        }
    }
    for(int i=1;i<6;i++){
        if(!regs[i].locked&&!regs[i].changed){
            std::cout<<"Reg "<<static_cast<char>(97+i)<<" isnt changed so freeing it\n";
            regs[i].freeRegister();
            return i;
        }
    }
    for(int i=1;i<6;i++){
        if(!regs[i].locked){
            std::cout<<"Reg "<<static_cast<char>(97+i)<<" is changed so storing it\n";
            buildAddress(regs[i].stored, 7);
            get(i);
            store(H);
            regs[i].freeRegister();
            return i;
        }
    }
    std::cout<<"\033[31;1;4mFAULT\033[0m ALL REGISTERS LOCKED\n";
    return -1;
}

int Architecture::getVal(Value* val){
    for(int i=1; i<6;i++){
        if(isSameVal(val, regs[i].stored)){
            std::cout<<"Gettign same val as "<<regs[i].stored->val<<std::endl;
            return i;
        }
    }
    int bestIndex = getBestFree();
    getInto(bestIndex, val);

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
    if(!dynamic_cast<Number*>(val)){
        load(A);
    }
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