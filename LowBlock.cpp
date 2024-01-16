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
            //STORE i
        }
        regs[i].freeRegister();
    }
}

void Architecture::dumpUnlocked(){
    for(int i=0;i<8;i++){
        if(!regs[i].locked){
            if(regs[i].changed){
                //STORE i
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
            //STORE i
            return i;
        }
    }
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

    //PUT bestIndex
    ////////////////////////////////////////////////
}

void Architecture::getInto(int i, Value* val){
    if(isSameVal(val, regs[i].stored)){
        return;
    }
    if(!regs[i].changed||regs[i].stored==nullptr){
        regs[i].freeRegister();
    }else{
        //STORE i
        regs[i].freeRegister();
    }
    getIntoA(val);

    //PUT i
    ///////////////////////////////////////////////
}

void Architecture::getIntoA(Value* val){
    for(int i=1;i<6;i++){
        if(isSameVal(val, regs[i].stored)){
            //GET i
            //////////////////////////////////////
            return;
        }
    }
    buildAddress(val,0);
    //LOAD a
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
    Builder* builder = new Builder();
    builder->numberBuild = number;
    builder->target = where;
}

int Architecture::putModifiedVal(Value* val){
    for(int i=1; i<6;i++){
        if(isSameVal(regs[i].stored, val)){
            regs[i].changed=true;
            //put(i);
            return i;
        }
    }
    int best = getBestFree();
    regs[best].changed=true;
    regs[best].stored = val;
    //put(best);
    return best;
}

void Architecture::buildAddress(Value* val, int where){
    if(dynamic_cast<IndentifierArrNumber*>(val)){
        if(isCallable(val)){
            IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
            Procedure* proc = dynamic_cast<Procedure*>(programPart);
            buildNum(proc->callableTable[array->val]->adress, 0);
            //load(a)
            //load(a)
            //put(e)
            Number* number = new Number();
            garbageCollector.push_back(number);
            number->val = array->address;
            getIntoA(number);
            //add(e)
            if(where!=0){
                //put(where)
            }

            ////////////////////////////////////////
            //build addres in a, load twice, put e
            //get index into a
            //add
        }else{
            IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
            buildNum(programPart->symbolTable[array->val]->adress, 0);
            //load(a)
            //put(e)
            Number* number = new Number();
            garbageCollector.push_back(number);
            number->val = array->address;
            getIntoA(number);
            //add(e)
            if(where!=0){
                //put(where)
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
            //load(a)
            //load(a)
            //put(e)
            Identifier* id = new Identifier();
            garbageCollector.push_back(id);
            id->val = array->address;
            getIntoA(id);
            //add(e)
            if(where!=0){
                //put(where)
            }

            ////////////////////////////////////////
            //build addres in a, load twice, put e
            //get index into a
            //add
            //load a
        }else{
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(val);
            buildNum(programPart->symbolTable[array->val]->adress, 0);
            //load(a)
            //put(e)
            Identifier* id = new Identifier();
            garbageCollector.push_back(id);
            id->val = array->address;
            getIntoA(id);
            //add(e)
            if(where!=0){
                //put(where)
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
            //load a
            if(where!=0){
                //put(where)
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