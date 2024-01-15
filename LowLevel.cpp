#include "./LowLevel.hpp"


void LowLevelBlock::print(){
    std::cout<<"B"+std::to_string(this->index)<<std::endl;
    for(int i=0;i<lowInstructions.size(); i++){
        std::cout<<lowInstructions[i]<<std::endl;
    }
}
// void LowConditional::print(){
//     std::cout<<"CONDITIONAL BLOCK";
// }

///////////////////////////////////////////////
//LOW LEVEL PROGRAM
///////////////////////////////////////////////

//yep can be broken down to subprocedures but not now. Im in hurry, copy paste is faster.
LowLevelProgram::LowLevelProgram(Program* whole){
    for (int i=0; i<8; i++){
        regs[i].number = i;
        regs[i].index = static_cast<char>(ASCII_LOWER_A+i);
        regs[i].locked=false;
        regs[i].wasNew = false;
        regs[i].stored=nullptr;
        regs[i].indexStored ="";
    }

    int memAddr=0;
    program = whole;
    
    for(auto pair : program->main->symbolTable){
        if(memAddr>MAX_MEM_SIZE||memAddr<0){
            isOverflow=true;
        }
        pair.second->adress = memAddr;
        memAddr++;
        memAddr+=pair.second->offset;
    }
    for(int i=0; i<program->procedures->procedures.size();i++){
        program->procedures->procedures[i]->initialAddr = memAddr;

        for(i=0; i<program->procedures->procedures[i]->head->args->argsVec.size();i++){
            if(memAddr>MAX_MEM_SIZE||memAddr<0){
                isOverflow=true;
            }
            Identifier* callable =program->procedures->procedures[i]->head->args->argsVec[i];
            Variable* var = program->procedures->procedures[i]->callableTable[callable->val];
            var->adress = memAddr;
            memAddr++;
            memAddr+=var->offset;
        }
        if(memAddr>MAX_MEM_SIZE||memAddr<0){
            isOverflow=true;
        }
        program->procedures->procedures[i]->retAddr = memAddr;
        memAddr++;
        for(auto pair : program->procedures->procedures[i]->symbolTable){
            if(memAddr>MAX_MEM_SIZE||memAddr<0){
                isOverflow=true;
            }
            pair.second->adress = memAddr;
            memAddr++;
            memAddr+=pair.second->offset;
        }

    }
    LowLevelBlock* block = new LowLevelBlock();
    std::vector<std::string> halt;
    halt.push_back("HALT");
    block->lowInstructions = halt;
    halter = block;
    halter->index = -1;
    initial = DFS(program->BBs->initialBlock);
}

LowLevelBlock* LowLevelProgram::DFS(Block* bloc){
    LowLevelBlock* lowBlock = translateBlock(bloc);
    lowBlock->index = bloc->index;
    if(dynamic_cast<LowConditional*> (lowBlock)){
        LowConditional* condBlock = dynamic_cast<LowConditional*> (lowBlock);
        if(bloc->ifFalse==nullptr){
            condBlock->elseNext = halter;
        }else{
            condBlock->elseNext = DFS(bloc->ifFalse);
        }
        if(bloc->ifTrue==nullptr){
            condBlock->next = halter;
        }else{
            condBlock->next = DFS(bloc->ifTrue);
        }
        return condBlock;
    }else{
        if(bloc->ifTrue==nullptr){
            lowBlock->next = halter;
        }else{
            lowBlock->next = DFS(bloc->ifTrue);
        }
        return lowBlock;
    }
}

void LowLevelProgram::printLowLevel(){
    std::stack<LowLevelBlock*> stack;
    stack.push(initial);
    while(!stack.empty()){
        LowLevelBlock* top = stack.top();
        stack.pop();
        if(!top->visited){
            if(dynamic_cast<LowConditional*> (top)){
                LowConditional* cond  = dynamic_cast<LowConditional*> (top);
                cond->print();
                std::cout<<"TRUE JUMP "+std::to_string(cond->next->index)<<std::endl;
                std::cout<<"FALSE JUMP "+std::to_string(cond->elseNext->index)+"\n\n";
                stack.push(cond->next);
                stack.push(cond->elseNext);
            }else{
                top->print();
                if(top!=halter){
                    std::cout<<"JUMP "+std::to_string(top->next->index)+"\n\n";
                    stack.push(top->next);
                }
            }
            top->visited=true;
        }
    }
}

LowLevelBlock* LowLevelProgram::translateBlock(Block* block){
    std::vector<std::string> translated;
    bool isConditional = false;
    for(int i=0; i<block->inst.size(); i++){
        Instruction* curr = block->inst[i];
        if(dynamic_cast<Assignment*>(curr)){
            handleAssignment(dynamic_cast<Assignment*>(curr), translated);
        }else if(dynamic_cast<Write*>(curr)){
            handleWrite(dynamic_cast<Write*>(curr), translated);
        }else if(dynamic_cast<Read*>(curr)){
            handleRead(dynamic_cast<Read*>(curr), translated);
        }else if(dynamic_cast<ConditionalSimple*>(curr)){
            handleCond(dynamic_cast<ConditionalSimple*>(curr)->cond, translated);
        }else if(dynamic_cast<Procedure_call*>(curr)){
            isConditional = true;
            handleCall(dynamic_cast<Procedure_call*>(curr), translated);
        }
    }
    if(isConditional){
        LowConditional* lowBlock = new LowConditional();
        lowBlock->lowInstructions = translated;
        return lowBlock;
    }
    LowLevelBlock* lowBlock = new LowLevelBlock();
    lowBlock->lowInstructions = translated;
    return lowBlock;
}

void LowLevelProgram::handleAssignment(Assignment* assign, std::vector<std::string>& translated){
    //storing into x[a] results in IMMEDIATE storage in memory
    valuePrecheck(assign->identifier, translated);
    //anything else isn't problematic so no problem :)
    if(dynamic_cast<ExprComplex*>(assign->expression)){
        ExprComplex* complex =  dynamic_cast<ExprComplex*>(assign->expression);
        int rightSide = getVal(complex->right, translated);
        regs[rightSide].locked = true;
        getValIntoA(complex->left, translated);
        regs[rightSide].locked = false;
        if(complex->operand=="+"){
            add(rightSide, translated);
        }else if(complex->operand=="-"){
            sub(rightSide, translated);
        }else if(complex->operand=="*"){
            mult(rightSide, translated);
        }else if(complex->operand=="/"){
            div(rightSide, translated);
        }else if(complex->operand=="%"){
            mod(rightSide, translated);
        }
    }else if(dynamic_cast<ExprSimple*>(assign->expression)){
        ExprSimple* simp = dynamic_cast<ExprSimple*>(assign->expression);
        getValIntoA(simp->left, translated);
    }
    putVal(assign->identifier, translated);
    valuePostcheck(assign->identifier, translated);
}

void LowLevelProgram::handleWrite(Write* write, std::vector<std::string>& translated){
    getValIntoA(write->val, translated);
    //can be further optimised to put val back into registers, but now it'll do
    translated.push_back("WRITE");
}

void LowLevelProgram::handleRead(Read* read, std::vector<std::string>& translated){
    valuePrecheck(read->ident, translated);
    translated.push_back("READ");
    putVal(read->ident, translated);
    valuePostcheck(read->ident, translated);
}

///////////////////////////////////////////////////////
//////////a>b -> a-b -> JPOS true JUMP false///////////
//////////a>=b -> b-a -> JZERO true JUMP false/////////
//a==b -> a-b -> JPOS false b-a JZERO true JUMP false//
///////////////////////////////////////////////////////
void LowLevelProgram::handleCond(Condition* cond, std::vector<std::string>& translated){
    if(cond->operand==">"){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        getValIntoA(cond->leftVal, translated);
        regs[right].locked = false;
        sub(right, translated);
        translated.push_back("JPOS true");
        translated.push_back("JUMP false");
    }else if(cond->operand==">="){
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->rightVal, translated);
        regs[left].locked = false;
        sub(left, translated);
        translated.push_back("JZERO true");
        translated.push_back("JUMP false");
    }else if(cond->operand=="=="){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->leftVal, translated);
        sub(right, translated);
        translated.push_back("JPOS false");
        getValIntoA(cond->rightVal, translated);
        sub(left, translated);
        translated.push_back("JPOS false");
        translated.push_back("JUMP true");
        regs[left].locked = false;
        regs[right].locked = false;
    }else if(cond->operand=="!="){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->leftVal, translated);
        sub(right, translated);
        translated.push_back("JPOS true");
        getValIntoA(cond->rightVal, translated);
        sub(left, translated);
        translated.push_back("JPOS true");
        translated.push_back("JUMP false");
        regs[left].locked = false;
        regs[right].locked = false;
    }else if(cond->operand=="<"){
        int left = getVal(cond->leftVal, translated);
        regs[left].locked = true;
        getValIntoA(cond->rightVal, translated);
        regs[left].locked = false;
        sub(left, translated);
        translated.push_back("JPOS true");
        translated.push_back("JUMP false");
    }else if(cond->operand=="<="){
        int right = getVal(cond->rightVal, translated);
        regs[right].locked = true;
        getValIntoA(cond->leftVal, translated);
        regs[right].locked = false;
        sub(right, translated);
        translated.push_back("JZERO true");
        translated.push_back("JUMP false");
    }
}

int LowLevelProgram::getVal(Value* val, std::vector<std::string>& translated){
    if(dynamic_cast<Number*>(val)){
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val){
                    return i;
                }
            }
        }
        
        for(int i=1; i<6;i++){
            if(regs[i].stored==nullptr){
                std::string operation = "BUILD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                operation=operation+" "+val->val;
                translated.push_back(operation);
                regs[i].stored = val;
                return i;
            }
        }

        for(int i=1; i<6; i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                std::string operation = "BUILD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                operation=operation+" "+val->val;
                translated.push_back(operation);
                regs[i].stored = val;
                return i;
            }
        }
    }else if(dynamic_cast<IndentifierArrPid*>(val)){
        IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(val);
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val&&array->address==regs[i].indexStored){
                    return i;
                }
            }
        }

        int addressRegister = getValFromString(array->address, translated);
        regs[addressRegister].locked = true;
        for(int i=1; i<6; i++){
            if(regs[i].stored==nullptr){
                translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[array->val]->adress));
                std::string operation = "ADD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+addressRegister));
                translated.push_back(operation);
                translated.push_back("LOAD a");
                operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = array;
                regs[i].indexStored = array->address;
                regs[addressRegister].locked = false;
                return i;
            }
        }

        for(int i=1; i<6; i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[array->val]->adress));
                std::string operation = "ADD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+addressRegister));
                translated.push_back(operation);
                translated.push_back("LOAD a");
                operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = array;
                regs[i].indexStored = array->address;
                regs[addressRegister].locked = false;
                return i;
            }
        }
        
    }else if(dynamic_cast<IndentifierArrNumber*>(val)){
        IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val&&array->address==regs[i].indexStored){
                    return i;
                }
            }
        }

        int addressRegister = getValFromNumber(stoull(array->address), translated);
        regs[addressRegister].locked = true;

        for(int i=1; i<6; i++){
            if(regs[i].stored==nullptr){
                translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[array->val]->adress));
                std::string operation = "ADD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+addressRegister));
                translated.push_back(operation);
                translated.push_back("LOAD a");
                operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = array;
                regs[i].indexStored = array->address;
                regs[addressRegister].locked = false;
                return i;
            }
        }

        for(int i=1; i<6; i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[array->val]->adress));
                std::string operation = "ADD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+addressRegister));
                translated.push_back(operation);
                translated.push_back("LOAD a");
                operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = array;
                regs[i].indexStored = array->address;
                regs[addressRegister].locked = false;
                return i;
            }
        }
    }else if(dynamic_cast<Identifier*>(val)){
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val){
                    return i;
                }
            }
        }
        
        for(int i=1; i<6;i++){
            if(regs[i].stored==nullptr){
                std::string operation = "BUILD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                operation=operation+" "+std::to_string(program->main->symbolTable[val->val]->adress);
                translated.push_back(operation);
                translated.push_back("LOAD a");
                operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);

                regs[i].stored = val;
                return i;
            }
        }

        for(int i=1; i<6; i++){
            if(!regs[i].locked){
                freeRegister(i, translated);
                std::string operation = "BUILD ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                operation=operation+" "+std::to_string(program->main->symbolTable[val->val]->adress);
                translated.push_back(operation);
                translated.push_back("LOAD a");
                operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);

                regs[i].stored = val;
                return i;
            }
        }
    }
}

int LowLevelProgram::getValFromString(std::string str, std::vector<std::string>& translated){
    for(int i=1;i<6;i++){
        if(regs[i].stored!=nullptr){
            if(regs[i].stored->val==str){
                return i;
            }
        }
    }
    Identifier* id = new Identifier();
    id->val = str;
    for(int i=1; i<6;i++){
        if(regs[i].stored==nullptr){
            std::string operation = "BUILD ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
            operation=operation+" "+std::to_string(program->main->symbolTable[str]->adress);
            translated.push_back(operation);
            translated.push_back("LOAD a");
            operation = "PUT ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
            translated.push_back(operation);
            regs[i].stored = id;
            regs[i].wasNew=true;
            return i;
        }
    }

    for(int i=1; i<6;i++){
        if(!regs[i].locked){
            freeRegister(i, translated);
            std::string operation = "BUILD ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
            operation=operation+" "+std::to_string(program->main->symbolTable[str]->adress);
            translated.push_back(operation);
            translated.push_back("LOAD a");
            operation = "PUT ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
            translated.push_back(operation);
            regs[i].stored = id;
            regs[i].wasNew=true;
            return i;
        }
    }
}

int LowLevelProgram::getValFromNumber(unsigned long long num, std::vector<std::string>& translated){
    std::string str = std::to_string(num);
    for(int i=1;i<6;i++){
        if(regs[i].stored!=nullptr){
            if(regs[i].stored->val==str){
                return i;
            }
        }
    }
    Number* id = new Number();
    id->val = str;
    for(int i=1; i<6;i++){
        if(regs[i].stored==nullptr){
            std::string operation = "BUILD ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
            operation=operation+" "+str;
            translated.push_back(operation);
            regs[i].stored = id;
            regs[i].wasNew=true;
            return i;
        }
    }
    
    for(int i=1; i<6; i++){
        if(!regs[i].locked){
            freeRegister(i, translated);
            std::string operation = "BUILD ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
            operation=operation+" "+str;
            translated.push_back(operation);
            regs[i].stored = id;
            regs[i].wasNew=true;
            return i;
        }
    }
}

void LowLevelProgram::valuePrecheck(Value* val, std::vector<std::string>& translated){
    //if val is simple identifier then check if any indexStored == val->val. if so, store this. of course only if was changed
    for(int i=1;i<6;i++){
        if(regs[i].indexStored==val->val){
            Value* stored = regs[i].stored;
            bool wasAvaible = false; 
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(stored);
            translated.push_back("BUILD e "+std::to_string(program->main->symbolTable[regs[i].stored->val]->adress));
            for(int j=1;j<6;j++){
                if(regs[j].stored!=nullptr){
                    if(regs[j].stored->val==array->address){
                        std::string operation = "GET ";
                        operation.push_back(static_cast<char>(ASCII_LOWER_A+j));
                        translated.push_back(operation);
                        wasAvaible=true;
                        break;
                    }
                }
            }
            if(!wasAvaible){
                translated.push_back("BUILD a "+ std::to_string(program->main->symbolTable[array->address]->adress));
            }
            translated.push_back("ADD e");
            translated.push_back("PUT e");
            std::string operation = "GET ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
            translated.push_back(operation);
            translated.push_back("STORE e");
        }
    }
}

void LowLevelProgram::valuePostcheck(Value* val, std::vector<std::string>& translated){
    //if val is simple identifier then check if any indexStored == val->val. if so, DELETE IT, SET NULL
    for(int i=1;i<6;i++){
        if(regs[i].indexStored==val->val){
            regs[i].indexStored = "";
            regs[i].locked=false;
            if(regs[i].wasNew){
                delete(regs[i].stored);
            }
            regs[i].stored = nullptr;
            regs[i].wasNew=false;
            regs[i].changed = false;
        }
    }
}

void LowLevelProgram::handleCall(Procedure_call* call, std::vector<std::string>& translated){
    dumpRegs(translated);
    unsigned long long addr = program->proceduresTable[call->name]->initialAddr;    
    translated.push_back("BUILD e "+std::to_string(addr));
    for(int i=0;i<call->args->argsVec.size();i++){
        Identifier* id = call->args->argsVec[i];
        translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[id->val]->adress));
        translated.push_back("STORE e");
        translated.push_back("INC e");
    }
    translated.push_back("STRK a");
    translated.push_back("STORE e");
    translated.push_back("JUMP procedure "+call->name);
    return;
}

void LowLevelProgram::dumpRegs(std::vector<std::string>& translated){
    for(int i=0; i<8; i++){
        if(!regs[i].locked){
            freeRegister(i, translated);
        }
    }
}

void LowLevelProgram::freeRegister(int num,std::vector<std::string>& translated){
    Value* stored = regs[num].stored;
    std::string index = regs[num].indexStored;
    if(regs[num].changed){
        if(dynamic_cast<IndentifierArrPid*>(stored)){
        //x[a], check if a is avaible, if is then build x adress in a, add a, store num
        //if no then build adress a in e, load a into e, build x adress in a, add e, store num 
            bool wasAvaible = false; 
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(stored);
            translated.push_back("BUILD e "+std::to_string(program->main->symbolTable[regs[num].stored->val]->adress));
            for(int i=1;i<6;i++){
                if(regs[i].stored!=nullptr){
                    if(regs[i].stored->val==array->address){
                        std::string operation = "GET ";
                        operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                        translated.push_back(operation);
                        wasAvaible=true;
                        break;
                    }
                }
            }
            if(!wasAvaible){
                translated.push_back("BUILD a "+ std::to_string(program->main->symbolTable[array->address]->adress));
            }
            translated.push_back("ADD e");
            translated.push_back("PUT e");
            std::string operation = "GET ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+num));
            translated.push_back(operation);
            translated.push_back("STORE e");
            
        }else if(dynamic_cast<IndentifierArrNumber*>(stored)){
        //x[5], check if 5 is avaible, if is then build x adress in a, add 5, store num
        //if no then build 5 in e, load a into e, build x adress in a, add e, store num
            bool wasAvaible = false; 
            IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(stored);
            translated.push_back("BUILD e "+std::to_string(program->main->symbolTable[regs[num].stored->val]->adress));
            
            for(int i=1;i<6;i++){
                if(regs[i].stored!=nullptr){
                    if(regs[i].stored->val==array->val){
                        std::string operation = "GET ";
                        operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                        translated.push_back(operation);
                        wasAvaible=true;
                        break;
                    }
                }
            }
            if(!wasAvaible){
                translated.push_back("BUILD a "+ array->address);
            }
            translated.push_back("ADD e");
            translated.push_back("PUT e");
            std::string operation = "GET ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+num));
            translated.push_back(operation);
            translated.push_back("STORE e");

        }else if(dynamic_cast<Identifier*>(stored)){
        //build address in e, store
            std::string operation = "GET ";
            operation.push_back(static_cast<char>(ASCII_LOWER_A+num));
            translated.push_back(operation);
            translated.push_back("BUILD e "+std::to_string(program->main->symbolTable[regs[num].stored->val]->adress));
            translated.push_back("STORE e");
        }   
    }
    regs[num].indexStored = "";
    regs[num].locked=false;
    if(regs[num].wasNew){
        delete(regs[num].stored);
    }
    regs[num].stored = nullptr;
    regs[num].wasNew=false;
    regs[num].changed = false;
}

int LowLevelProgram::putVal(Value* val, std::vector<std::string>& translated){
    if(dynamic_cast<Number*>(val)){
        for(int i=0; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==val->val){
                    return i;
                }
            }
        }
        for(int i=1; i<6;i++){
            if(regs[i].stored==nullptr){
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                return i;
            }
        }
        for(int i=1; i<6;i++){
            if(!regs[i].locked){
                translated.push_back("PUT f");
                freeRegister(i, translated);
                translated.push_back("GET f");
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                return i;
            }
        }
    }else if(dynamic_cast<IndentifierArrPid*>(val)){
        IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(val);
        for(int i=0; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==val->val&&regs[i].indexStored==array->address){
                    std::string operation = "PUT ";
                    operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                    translated.push_back(operation);
                    regs[i].changed=true;
                    return i;
                }
            }
        }
        for(int i=1; i<6;i++){
            if(regs[i].stored==nullptr){
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                regs[i].indexStored=array->address;
                regs[i].changed=true;
                return i;
            }
        }
        for(int i=1; i<6;i++){
            if(!regs[i].locked){
                translated.push_back("PUT f");
                freeRegister(i, translated);
                translated.push_back("GET f");
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                regs[i].indexStored=array->address;
                regs[i].changed=true;
                return i;
            }
        }
       
    }else if(dynamic_cast<IndentifierArrNumber*>(val)){
        IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
        for(int i=0; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==val->val&&regs[i].indexStored==array->address){
                    std::string operation = "PUT ";
                    operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                    translated.push_back(operation);
                    regs[i].changed=true;
                    return i;
                }
            }
        }
        for(int i=1; i<6;i++){
            if(regs[i].stored==nullptr){
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                regs[i].indexStored=array->address;
                regs[i].changed=true;
                return i;
            }
        }
        for(int i=1; i<6;i++){
            if(!regs[i].locked){
                translated.push_back("PUT f");
                freeRegister(i, translated);
                translated.push_back("GET f");
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                regs[i].indexStored=array->address;
                regs[i].changed=true;
                return i;
            }
        }
    }else if(dynamic_cast<Identifier*>(val)){
        for(int i=0; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(regs[i].stored->val==val->val){
                    std::string operation = "PUT ";
                    operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                    translated.push_back(operation);
                    regs[i].changed=true;
                    return i;
                }
            }
        }
        for(int i=1; i<6;i++){
            if(regs[i].stored==nullptr){
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                regs[i].changed=true;
                return i;
            }
        }
        for(int i=1; i<6;i++){
            if(!regs[i].locked){
                translated.push_back("PUT f");
                freeRegister(i, translated);
                translated.push_back("GET f");
                std::string operation = "PUT ";
                operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                translated.push_back(operation);
                regs[i].stored = val;
                regs[i].changed=true;
                return i;
            }
        }
    }
}

void LowLevelProgram::getValIntoA(Value* val, std::vector<std::string>& translated){
    if(dynamic_cast<Number*>(val)){
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val){
                    std::string operation = "GET ";
                    operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                    translated.push_back(operation);
                    return;
                }
            }
        }
        translated.push_back("BUILD a "+val->val);
        return;
    }else if(dynamic_cast<IndentifierArrPid*>(val)){
        IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(val);
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val&&array->address==regs[i].indexStored){
                    std::string operation = "GET ";
                    operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                    translated.push_back(operation);
                    return;
                }
            }
        }

        int addressRegister = getValFromString(array->address, translated);
        //regs[addressRegister].locked = true;
        translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[array->val]->adress));
        std::string operation = "ADD ";
        operation.push_back(static_cast<char>(ASCII_LOWER_A+addressRegister));
        translated.push_back(operation);
        translated.push_back("LOAD a");
        return;
        
    }else if(dynamic_cast<IndentifierArrNumber*>(val)){
        IndentifierArrNumber* array = dynamic_cast<IndentifierArrNumber*>(val);
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val&&array->address==regs[i].indexStored){
                    std::string operation = "GET ";
                    operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                    translated.push_back(operation);
                    return;
                }
            }
        }

        int addressRegister = getValFromNumber(stoull(array->address), translated);
        //regs[addressRegister].locked = true;
        translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[array->val]->adress));
        std::string operation = "ADD ";
        operation.push_back(static_cast<char>(ASCII_LOWER_A+addressRegister));
        translated.push_back(operation);
        translated.push_back("LOAD a");
        return;

    }else if(dynamic_cast<Identifier*>(val)){
        for(int i=1; i<6;i++){
            if(regs[i].stored!=nullptr){
                if(val->val==regs[i].stored->val){
                    std::string operation = "GET ";
                    operation.push_back(static_cast<char>(ASCII_LOWER_A+i));
                    translated.push_back(operation);
                    return;
                }
            }
        }
        translated.push_back("BUILD a "+std::to_string(program->main->symbolTable[val->val]->adress));
        translated.push_back("LOAD a");
        return;
    }
}

void LowLevelProgram::add(int reg, std::vector<std::string>& translated){
    std::string operation = "ADD ";
    operation.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    translated.push_back(operation);
}

void LowLevelProgram::sub(int reg, std::vector<std::string>& translated){
    std::string operation = "SUB ";
    operation.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    translated.push_back(operation);
}

void LowLevelProgram::mult(int reg, std::vector<std::string>& translated){
    std::string operation = "MULT ";
    operation.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    translated.push_back(operation);
}

void LowLevelProgram::div(int reg, std::vector<std::string>& translated){
    std::string operation = "DIV ";
    operation.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    translated.push_back(operation);
}

void LowLevelProgram::mod(int reg, std::vector<std::string>& translated){
    std::string operation = "MOD ";
    operation.push_back(static_cast<char>(ASCII_LOWER_A+reg));
    translated.push_back(operation);
}