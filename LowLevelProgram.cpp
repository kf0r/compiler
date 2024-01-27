#include "./LowBlock.hpp"

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

            if(comp->operand=="/"){
                arch->isDiv = true;
                arch->div();
            }else if(comp->operand=="%"){
                arch->isDiv = true;
                arch->mod();
            }else if(comp->operand=="*"){
                arch->isMult = true;
                arch->mult();
            }
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

    }else if(cond->operand=="="){
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

    /////////////////////// JUMP TO PROCEDURE
    arch->jump(call->name);
    arch->clearAll();;
}

void LowLevelProgram::handleReturn(){
    //if main just halt
    //if procedure store callable jump to return address
    if(dynamic_cast<Procedure*>(arch->programPart)){
        Procedure* proc = dynamic_cast<Procedure*>(arch->programPart);
        arch->returnMerger();
        arch->storeReturn();
        arch->buildNum(proc->retAddr, A);
        arch->load(A);
        arch->inc(A);
        arch->inc(A);
        arch->inc(A);
        arch->jumpr(A);
    }else{
        arch->returnMerger();
        arch->haltMain();
    }
}

void LowLevelProgram::setReturns(LowLevelBlock* lowBlock, Block* block){
    if(lowBlock->isCond){
        if(block->ifTrue==nullptr||block->ifFalse==nullptr){
            handleReturn();
        }
    }else{
        if(block->ifTrue==nullptr){
            handleReturn();
        }
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
        }else if(dynamic_cast<ConditionalSimple*>(block->inst[i])){
            isCond=true;
            handleCond(dynamic_cast<ConditionalSimple*>(block->inst[i])->cond);
        }else if(dynamic_cast<Procedure_call*>(block->inst[i])){
            handleCall(dynamic_cast<Procedure_call*>(block->inst[i]));
        }
    }
    lowBlock->isCond = isCond;
    lowBlock->index = block->index;
    block->visited = true;
    mapBlock.insert(std::pair<int, LowLevelBlock*> (lowBlock->index, lowBlock));
    setReturns(lowBlock,block);
    if(!isCond){
        if(block->ifTrue!=nullptr){
            arch->dumpAll();
            arch->jump("NEXTBLOCK");
        }
    }
    if(block->ifFalse!=nullptr){
        lowBlock->nextElse=generateLowBB(block->ifFalse);
    }
    arch->clearAll();
    if(block->ifTrue!=nullptr){
        lowBlock->next=generateLowBB(block->ifTrue);
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
    arch->clearAll();
    if(arch->isDiv){
        generateDiv();
    }
    arch->clearAll();
    if(arch->isMult){
        generateMult();
    }
    link(mainBlock);
    for(int i=0;i<program->procedures->procedures.size();i++){
        std::string name = program->procedures->procedures[i]->head->name;
        link(proceduresBlock[name]);
    }
    generateAssembly();
}

void LowLevelProgram::link(LowLevelBlock* block){
    std::stack<LowLevelBlock*> stack;
    stack.push(block);
    while(!stack.empty()){
        LowLevelBlock* top = stack.top();
        top->visited=true;
        stack.pop();
        for(int i=0;i<top->jumpers.size();i++){
            if(dynamic_cast<Jump*>(top->jumpers[i])){
                Jump* jump = dynamic_cast<Jump*>(top->jumpers[i]);
                if(jump->where!="NEXTBLOCK"){
                    jump->jumpTo = proceduresBlock[jump->where]->instr[0];
                }else{
                    jump->jumpTo = top->next->instr[0];
                }
            }else if(dynamic_cast<JPos*>(top->jumpers[i])){
                JPos* jpos = dynamic_cast<JPos*>(top->jumpers[i]);
                if(jpos->condition){
                    if(top->next){
                        jpos->jumpTo = top->next->instr[0];
                    }else if(top->merger){
                        jpos->jumpTo = top->merger;
                    }else{
                        std::cout<<"\033[31;1;4mFAULT\033[0m no merger and no next block\n";
                    }
                }else{
                    if(top->nextElse){
                        std::cout<<top->index<<std::endl;
                        jpos->jumpTo = top->nextElse->instr[0];
                    }else if(top->merger){
                        jpos->jumpTo = top->merger;
                    }else{
                        std::cout<<"\033[31;1;4mFAULT\033[0m no merger and no next block\n";
                    }
                }
            }else if(dynamic_cast<JZero*>(top->jumpers[i])){
                JZero* jzero = dynamic_cast<JZero*>(top->jumpers[i]);
                if(jzero->condition){
                    if(top->next){
                        jzero->jumpTo = top->next->instr[0];
                    }else if(top->merger){
                        jzero->jumpTo = top->merger;
                    }else{
                        std::cout<<"\033[31;1;4mFAULT\033[0m no merger and no next block\n";
                    }
                }else{
                    if(top->nextElse){
                        jzero->jumpTo = top->nextElse->instr[0];
                    }else if(top->merger){
                        jzero->jumpTo = top->merger;
                    }else{
                        std::cout<<"\033[31;1;4mFAULT\033[0m no merger and no next block\n";
                    }
                }
            }
        }
        if(!top->isCond){

        }
        if(top->next!=nullptr){
            if(!top->next->visited){
                stack.push(top->next);
            }
        }
        if(top->nextElse!=nullptr){
            if(!top->nextElse->visited){
                stack.push(top->nextElse);
            }
        }
    }
}

void LowLevelProgram::generateAssembly(){
    std::vector<LowInstruction*> assembly;
    getMachineCode(assembly, mainBlock);
    for(auto pair:proceduresBlock){
        getMachineCode(assembly, pair.second);
    }
    std::sort(assembly.begin(), assembly.end(), compareIndexes);
    for(int i=0;i<assembly.size();i++){
        std::cout<<assembly[i]->toString()<<std::endl;
    }
}

void LowLevelProgram::getMachineCode(std::vector<LowInstruction*>& instructions, LowLevelBlock* block){
    std::stack<LowLevelBlock*> stack;
    stack.push(block);
    while(!stack.empty()){
        LowLevelBlock* top = stack.top();
        stack.pop();
        top->visited=false;
        for(int i=0;i<top->instr.size();i++){
            if(!dynamic_cast<ReturnMerger*>(top->instr[i])){
                instructions.push_back(top->instr[i]);
            }
        }
        if(top->next!=nullptr){
            if(top->next->visited){
                stack.push(top->next);
            }
        }
        if(top->nextElse!=nullptr){
            if(top->nextElse->visited){
                stack.push(top->nextElse);
            }
        }
    }
}

bool LowLevelProgram::compareIndexes(LowInstruction* a, LowInstruction* b){
    return a->index < b->index;
}