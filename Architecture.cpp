#include "./Architecture.hpp"



Arch::Arch(){
    for (int i=0; i<8; i++){
        regs[i].number = i;
        regs[i].index = static_cast<char>(ASCII_LOWER_A+i);
        regs[i].locked=false;
        regs[i].stored=nullptr;
    }
}

std::string Arch::getVar(Identifier* identifier){
    if(!identifier->isArray()){
        //easy
        //check if in register
        //if yes, get 
        //if no, build adress, load a, put free_reg
    }else{
        if(dynamic_cast<IndentifierArrPid*>(identifier)){
            //check if theres address variable stored in registers
            //build address of var, add variable adress
            //load a,put free_reg
        }else{
            //build address, add number, load a, put free_reg 
        }
    }
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





