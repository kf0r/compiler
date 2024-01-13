#include "./Architecture.hpp"



Arch::Arch(){
    for (int i=0; i<8; i++){
        regs[i].number = i;
        regs[i].index = static_cast<char>(ASCII_LOWER_A+i);
        regs[i].locked=false;
        regs[i].stored=nullptr;
        regs[i].indexStored = nullptr;
    }
}

std::string Arch::getValIntoA(Value* identifier){
    if(!identifier->isArray()){
        //easy
        //check if in register
        //if yes, get register
        //if no, build adress, load e
    }else{
        if(dynamic_cast<IndentifierArrPid*>(identifier)){
            //check if theres address variable stored in registers
            //build address of var, add variable adress
            //load e
        }else{
            //build address, add number, load e
        }
    }
}

std::string Arch::getVal(Value* identifier){
    if(!identifier->isArray()){
        //easy
        //check if in register
        //if yes, dont do antything
        //if no, build adress, load e, put free reg
    }else{
        if(dynamic_cast<IndentifierArrPid*>(identifier)){
            //check if theres address variable stored in registers
            //build address of var, add variable adress
            //load e, put free_reg
        }else{
            //build address, add number, load e, put free_reg 
        }
    }
}

std::string Arch::putVal(Value* val){
    //if number, build number in free register
    //if normal variable, check if its index of any arrays in registers, if is free that register, put in free register
    //if array put into free register and set index in register;
}

std::string Arch::freeRegister(int num){
    //check if contains var and isnt locked
    //build address, store
    //set variable to null
}

std::string Arch::dumpRegs(){
    for(int i=0; i<8; i++){
        freeRegister(i);
    }
}





