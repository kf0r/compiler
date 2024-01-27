#include "LowBlock.hpp"

int ASCII_LOWER_A = 97;

void Architecture::buildNum(unsigned long long number, int where){
    std::string stul = std::bitset<64>(number).to_string();

    int index =0;
    for(index; index<stul.size();index++){
        if(stul[index]=='1'){
            break;
        }
    }
    rst(where);
    if(index==64){
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
    //std::cout<<"krzysztof fornal\n";
    ReturnMerger* merger = new ReturnMerger();
    merger->index = counter;
    merger->inst = "MERGER";
    currBlock->merger = merger;
    currBlock->instr.push_back(merger);
}

void Architecture::add(int right){
    LowInstruction* add = new LowInstruction();
    add->index = counter;
    add->inst = "ADD ";
    add->inst.push_back(static_cast<char>(ASCII_LOWER_A+right));
    counter++;
    currBlock->instr.push_back(add);
}

void Architecture::sub(int right){
    LowInstruction* sub = new LowInstruction();
    sub->index = counter;
    sub->inst = "SUB ";
    sub->inst.push_back(static_cast<char>(ASCII_LOWER_A+right));
    counter++;
    currBlock->instr.push_back(sub);
}

void Architecture::mult(){
    clearExplicit(G);
    clearExplicit(F);
    clearExplicit(C);
    clearExplicit(B);
    strk(H);
    jump("*");
}

void Architecture::div(){
    storeAll();
    strk(H);
    jump("/");
    clearAll();
    get(G);
}

void Architecture::mod(){
    storeAll();
    strk(H);
    jump("/");
    clearAll();
    get(B);
}

void Architecture::read(){
    LowInstruction* read = new LowInstruction();
    read->index = counter;
    read->inst = "READ";
    counter++;
    currBlock->instr.push_back(read);
}

void Architecture::write(){
    LowInstruction* write = new LowInstruction();
    write->index = counter;
    write->inst = "WRITE";
    counter++;
    currBlock->instr.push_back(write);
}

void Architecture::rst(int reg){
    LowInstruction* rst = new LowInstruction();
    rst->index = counter;
    rst->inst = "RST ";
    rst->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(rst);
}

void Architecture::dec(int reg){
    LowInstruction* dec = new LowInstruction();
    dec->index = counter;
    dec->inst = "DEC ";
    dec->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(dec);
}

void Architecture::inc(int reg){
    LowInstruction* inc = new LowInstruction();
    inc->index = counter;
    inc->inst = "INC ";
    inc->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(inc);
}

void Architecture::shl(int reg){
    LowInstruction* shl = new LowInstruction();
    shl->index = counter;
    shl->inst = "SHL ";
    shl->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(shl);
}

void Architecture::shr(int reg){
    LowInstruction* shr = new LowInstruction();
    shr->index = counter;
    shr->inst = "SHR ";
    shr->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(shr);
}

void Architecture::put(int reg){
    LowInstruction* put = new LowInstruction();
    put->index = counter;
    put->inst = "PUT ";
    put->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(put);
}

void Architecture::get(int reg){    
    LowInstruction* get = new LowInstruction();
    get->index = counter;
    get->inst = "GET ";
    get->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(get);
}

void Architecture::load(int reg){
    LowInstruction* load = new LowInstruction();
    load->index = counter;
    load->inst = "LOAD ";
    load->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(load);
}

void Architecture::store(int reg){
    LowInstruction* stor = new LowInstruction();
    stor->index = counter;
    stor->inst = "STORE ";
    stor->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(stor);
}

void Architecture::strk(int reg){
    LowInstruction* strk = new LowInstruction();
    strk->index = counter;
    strk->inst = "STRK ";
    strk->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(strk);
}

void Architecture::jump(std::string procName){
    Jump* jump = new Jump();
    jump->index = counter;
    jump->inst = "JUMP ";
    counter++;
    jump->jumpTo = nullptr;
    jump->where=procName;
    currBlock->instr.push_back(jump);
    currBlock->jumpers.push_back(jump);
}

void Architecture::jumpr(int reg){
    LowInstruction* jumpr = new LowInstruction();
    jumpr->index = counter;
    jumpr->inst = "JUMPR ";
    jumpr->inst.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    counter++;
    currBlock->instr.push_back(jumpr);
}
    
void Architecture::jzero(bool cond){
    JZero* jz = new JZero();
    jz->index = counter;
    jz->inst = "JZERO ";
    jz->jumpTo = nullptr;
    jz->condition=cond;
    counter++;
    currBlock->instr.push_back(jz);
    currBlock->jumpers.push_back(jz);
}

void Architecture::jpos(bool cond){
    JPos* jp = new JPos();
    jp->index = counter;
    jp->inst = "JPOS ";
    jp->jumpTo = nullptr;
    jp->condition=cond;
    counter++;
    currBlock->instr.push_back(jp);
    currBlock->jumpers.push_back(jp);
}

void Architecture::haltMain(){
    LowInstruction* halt = new LowInstruction();
    halt->index = counter;
    halt->inst = "HALT ";
    counter++;
    currBlock->instr.push_back(halt);
}