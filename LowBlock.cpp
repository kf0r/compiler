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
    array = false;
    stored = nullptr;
}

void Register::freeRegister(){
    changed = false;
    locked = false;
    array = false;
    stored = nullptr;
}

////////////////////////////////////////////////////////////////
//
//Architecture
////////////////////////////////////////////////////////////////
Architecture::Architecture():regs{{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}}{
    currentPart="";
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
    prepareToLoad(val);
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

}

int Architecture::putValAnywhere(Value* val){

}

void Architecture::prepareToLoad(Value* val){

}

void store(int index){

}

////////////////////////////////////////////////////////////////
//
//LowLevelProgram
////////////////////////////////////////////////////////////////

LowLevelProgram::LowLevelProgram(Program* whole){
    program = whole;
}