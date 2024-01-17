#include "LowBlock.hpp"

void Architecture::buildNum(unsigned long long number, int where){
    std::string stul = std::bitset<64>(number).to_string();

    int index =0;
    for(index; index<stul.size();index++){
        if(stul[index]=='1'){
            break;
        }
    }
    if(index==64){
        rst(where);
        return;
    }
    index++;
    inc(where);
    for(index; index<stul.size();index++){
        shl(where);
        if(stul[index]=='1'){
            inc(where);
        }
    }
}

void Architecture::returnMerger(){
    std::cout<<""<<std::endl;
}

void Architecture::add(int right){
std::cout<<"ADD "<<static_cast<char>(97+right)<<std::endl;
}

void Architecture::sub(int right){
std::cout<<"SUB "<<static_cast<char>(97+right)<<std::endl;
}

void Architecture::mult(){
std::cout<<"MULT "<<std::endl;
}

void Architecture::div(){
std::cout<<"DIV "<<std::endl;
}

void Architecture::mod(){
std::cout<<"MOD "<<std::endl;
}

void Architecture::read(){
std::cout<<"READ "<<std::endl;
}

void Architecture::write(){
std::cout<<"WRITE "<<std::endl;
}

void Architecture::rst(int reg){
std::cout<<"RST"<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::dec(int reg){
std::cout<<"DEC"<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::inc(int reg){
std::cout<<"INC "<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::shl(int reg){
std::cout<<"SHL "<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::shr(int reg){
std::cout<<"SHR"<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::put(int reg){
std::cout<<"PUT "<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::get(int reg){
std::cout<<"GET "<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::load(int reg){
    std::cout<<"LOAD "<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::store(int reg){
std::cout<<"STORE "<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::strk(int reg){
std::cout<<"STRK "<<static_cast<char>(97+reg)<<std::endl;
}

void Architecture::jump(std::string procName){
std::cout<<"JUMP "<<procName<<std::endl;
}

void Architecture::jumpr(int reg){
std::cout<<"JUMPR"<<static_cast<char>(97+reg)<<std::endl;
}
    
void Architecture::jzero(bool cond){
std::cout<<"JZERO "<<std::endl;
}

void Architecture::jpos(bool cond){
std::cout<<"JPOS "<<std::endl;
}

void Architecture::haltMain(){
    std::cout<<"HALT"<<std::endl;
}