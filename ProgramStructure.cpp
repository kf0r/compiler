#include "./ProgramStructure.hpp"
#include <stack>
#include <iostream>
#include <thread>
#include <chrono>
#include <list>

unsigned long long MAXSIZE = 4611686018427387904;

void Program::procedureRedeclarations(){
    for(int i=0; i<procedures->procedures.size();i++){
        Procedure* current = procedures->procedures[i];
        std::string currentName = current->head->name;
        if(proceduresTable.find(currentName)!=proceduresTable.end()){
            std::cout<<"Redeklaracja procedury "<<currentName<<std::endl;
            valid = false;
        }else{
            proceduresTable.insert(std::pair<std::string, Procedure*>(currentName, current));
        }
    }
}

void Program::variableRedeclaration(Program_part* programPart){
    if(dynamic_cast<Procedure*>(programPart)){
        Procedure* proc = dynamic_cast<Procedure*>(programPart);
        if(proc->decs!=nullptr){
        for(int i=0;i<proc->decs->decsVec.size();i++){

            Identifier* id = proc->decs->decsVec[i];
            if(proc->symbolTable.find(id->val)!=proc->symbolTable.end()){
                std::cout<<"Redeklaracja zmiennej "<<id->val<<" w procedurze "<<proc->head->name<<std::endl;
                valid = false;
            }
            insertSymbol(proc, id);
        }
        }
        for(int i=0;i<proc->head->args->argsVec.size();i++){
            bool shouldInsert = true;
            Identifier* id = proc->head->args->argsVec[i];

            if(proc->symbolTable.find(id->val)!=proc->symbolTable.end()){
                std::cout<<"Zmienna "<<id->val<<" wcześniej zadeklarowana w DEKLARACJACH w "<<proc->head->name<<std::endl;
                valid = false;
                shouldInsert = false;
            }
            if(proc->callableTable.find(id->val)!=proc->callableTable.end()){
                std::cout<<"Zmienna "<<id->val<<" wcześniej zadeklarowana w ARGUMENTACH w "<<proc->head->name<<std::endl;
                valid = false;
                shouldInsert = false;
            }
            insertCall(proc, id);
        }
    }else{
        for(int i=0;i<programPart->decs->decsVec.size();i++){
            Identifier* id = programPart->decs->decsVec[i];
            if(programPart->symbolTable.find(id->val)!=programPart->symbolTable.end()){
                std::cout<<"Redeklaracja zmiennej "<<id->val<<" w MAIN"<<std::endl;
                valid = false;
            }else{
                insertSymbol(programPart, id);
            }

        }
    }
}

void Program::DFS(Program_part* part){
    std::stack<Instruction*> instStack;
    instStack.push(part->comms->getHead());
    while(!instStack.empty()){
        
        Instruction* top = instStack.top();
        instStack.pop();
        if(!top->visited){
            top->visited = true;
            for(int i=0; i<top->getNext().size();i++){
                if(top->getNext()[i]!=nullptr){
                    if(!top->getNext()[i]->visited){
                        instStack.push(top->getNext()[i]);
                    }
                }
            }
            if(dynamic_cast<Procedure_call*>(top)){
                validateCall(part,dynamic_cast<Procedure_call*>(top));
            }else{
                std::vector<Identifier*> identifiers = top->getVars();
                for(int i=0;i<identifiers.size();i++){
                    validateVariableUsage(part, identifiers[i]);
                }
            }
        }
    }
}

void Program::reset(Program_part* part){
    std::stack<Instruction*> instStack;
    instStack.push(part->comms->getHead());
    while(!instStack.empty()){
        Instruction* top = instStack.top();
        instStack.pop();
        if(top->visited){
            top->visited = false;
            for(int i=0; i<top->getNext().size();i++){
                if(top->getNext()[i]!=nullptr){
                    if(top->getNext()[i]->visited){
                        instStack.push(top->getNext()[i]);
                    }
                }
            }
        }
    }
}

void Program::BFS(Program_part* part){
    std::list<Instruction*> queue;
    queue.push_back(part->comms->getHead());
    while(!queue.empty()){
        Instruction* inst = queue.front();
        queue.pop_front();
        if(!inst->visited){
            inst->visited=true;
            for(int i=0; i<inst->getNext().size();i++){
                if(inst->getNext()[i]!=nullptr){
                    if(!inst->getNext()[i]->visited){
                        queue.push_back(inst->getNext()[i]);
                    }
                }
            }
            if(dynamic_cast<Assignment*>(inst)){
                setInitialized(part, dynamic_cast<Assignment*>(inst)->identifier);
            }else if(dynamic_cast<Read*>(inst)){
                setInitialized(part, dynamic_cast<Read*>(inst)->ident);
            }
            for(int i=0;i<inst->getVars().size();i++){
                setUsage(part,inst->getVars()[i]);
                checkInitialisations(part, inst->getVars()[i]);
            }
        }
    }
}

void Program::insertSymbol(Program_part* programPart, Identifier* id){
    Variable* var = new Variable();
    var->id = id->val;
    if(dynamic_cast<IndentifierArrNumber*>(id)){
        IndentifierArrNumber* array =  dynamic_cast<IndentifierArrNumber*>(id);
        var->isOffsettable = true;
        var->offset = stoull(array->address);
    }else{
        var->isOffsettable = false;
    }
    programPart->symbolTable.insert(std::pair<std::string, Variable*>(var->id, var));
}

void Program::insertCall(Procedure* procedure, Identifier* id){
    Variable* var = new Variable();
    var->id = id->val;
    if(id->isArray()){
        var->isOffsettable = true;
    }else{
        var->isOffsettable = false;
    }
    var->isInitialized = true;
    var->isUsed = true;
    //std::cout<<var->id;
    procedure->callableTable.insert(std::pair<std::string, Variable*>(var->id, var));
}

void Program::setInitialized(Program_part* part, Identifier* id){
    if(part->symbolTable.find(id->val)!=part->symbolTable.end()){
        part->symbolTable[id->val]->isInitialized=true;
    }
}

void Program::setUsage(Program_part* part, Identifier* id){
    if(part->symbolTable.find(id->val)!=part->symbolTable.end()){
        part->symbolTable[id->val]->isUsed=true;
    }   
}

void Program::checkInitialisations(Program_part* part, Identifier* id){
    if(part->symbolTable.find(id->val)!=part->symbolTable.end()){
        if(!part->symbolTable[id->val]->isInitialized&&!part->symbolTable[id->val]->isOffsettable){
            std::cout<<"Mozliwe uzycie niezainicjalizowanej zmiennej "<<id->val<<" w ";
            if(dynamic_cast<Procedure*>(part)){
                std::cout<<dynamic_cast<Procedure*>(part)->head->name<<std::endl;
            }else{
                std::cout<<"MAIN\n";
            }
        }
    }
    if(dynamic_cast<IndentifierArrPid*>(id)){
        IndentifierArrPid* array= dynamic_cast<IndentifierArrPid*>(id);
        Identifier* temp = new Identifier();
        temp->val = array->address;
        checkInitialisations(part, temp);
        delete(temp);  
    }
}

void Program::validateVariableUsage(Program_part* part, Identifier* identifier){
    if(dynamic_cast<Procedure*>(part)){
        Procedure* proc = dynamic_cast<Procedure*>(part);
        if(proc->symbolTable.find(identifier->val)!=proc->symbolTable.end()){
            Variable* var = proc->symbolTable[identifier->val];
            if(var->isOffsettable!=identifier->isArray()){
                std::cout<<"Nieprawidłowe uzycie tablicy "<<identifier->val<<" w procedurze "<<proc->head->name<<std::endl;
                valid=false;
            }
        }else if(proc->callableTable.find(identifier->val)!=proc->callableTable.end()){
            Variable* var = proc->callableTable[identifier->val];
            if(var->isOffsettable!=identifier->isArray()){
                std::cout<<"Nieprawidłowe uzycie tablicy "<<identifier->val<<" w procedurze "<<proc->head->name<<std::endl;
                valid=false;
            }
        }else{
            std::cout<<"Uzycie nieznanej zmiennej "<<identifier->val<<" w procedurze "<<proc->head->name<<std::endl;
            valid=false;
        }
        if(dynamic_cast<IndentifierArrPid*>(identifier)){
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(identifier);
            std::string address = array->address;
            if(part->symbolTable.find(address)==part->symbolTable.end()&&proc->callableTable.find(address)==proc->callableTable.end()){
                valid=false;
                std::cout<<"Uzycie nieznanego adresu "<<address<<" tablicy "<<identifier->val<<" w procedurze "<<proc->head->name<<std::endl;
            }
        }
    }else{
        if(part->symbolTable.find(identifier->val)==part->symbolTable.end()){
            valid = false;
            std::cout<<"Uzycie nieznanej zmiennej "<<identifier->val<<" w MAIN "<<std::endl;
        }else{
            Variable* var = part->symbolTable[identifier->val];
            if(var->isOffsettable!=identifier->isArray()){
                std::cout<<"Nieprawidłowe uzycie tablicy "<<identifier->val<<" w MAIN "<<std::endl;
                valid=false;
            }
            if(dynamic_cast<IndentifierArrPid*>(identifier)){
                IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(identifier);
                std::string address = array->address;
                if(part->symbolTable.find(address)==part->symbolTable.end()){
                    valid=false;
                    std::cout<<"Uzycie nieznanego adresu "<<address<<" tablicy "<<identifier->val<<" w MAIN "<<std::endl;
                }
            }
        }
    }
}

void Program::validateCall(Program_part* part, Procedure_call* call){
    if(dynamic_cast<Procedure*>(part)){
        if(!validateCallProc(call, dynamic_cast<Procedure*>(part))){
            valid = false;
        }
    }else{
        if(!validateCallMain(call)){
            valid = false;
        }
    }
}

bool Program::validateCallProc(Procedure_call* call, Procedure* current){
    if(proceduresTable.find(call->name)==proceduresTable.end()){
        std::cout<<"Wywołanie nieznanej funkcji "<<call->name<<" w "<<current->head->name<<std::endl; 
        return false;
    }
    if(call->name==current->head->name){
        std::cout<<"Rekurencyjne wywolanie "<<call->name<<" w "<<current->head->name<<std::endl; 
        return false;
    }
    if(proceduresTable[call->name]->head->args->argsVec.size()!=call->args->argsVec.size()){
        std::cout<<"Nieprawidłowa ilość argumentow funkcji " <<call->name<<" w "<<current->head->name<<std::endl;
        return false;
    }
    for(int i=0; i<proceduresTable[call->name]->head->args->argsVec.size(); i++){
        Identifier* inCalled = proceduresTable[call->name]->head->args->argsVec[i];
        Identifier* given = call->args->argsVec[i];
        Variable* varInCalled = proceduresTable[call->name]->callableTable[inCalled->val];
        Variable* varGiven;

        if(current->symbolTable.find(given->val)!=current->symbolTable.end()){
            varGiven = current->symbolTable[given->val];
        }else if(current->callableTable.find(given->val)!=current->callableTable.end()){
            varGiven = current->callableTable[given->val];
        }else{
            std::cout<<"Nieznany argument przy wywołaniu funkcji "<<call->name<<" w "<<current->head->name<<std::endl;
            return false;
        }

        if(varInCalled->isOffsettable){
            //We get indeksed array, so not array, but element of an array, so error.
            if(given->isArray()){
                std::cout<<"Funkcja "<<call->name<<" oczekuje tablicy, a dostała element tablicy "<<given->val<<" w "<<current->head->name<<std::endl;
                return false; 
            }else if(!varGiven->isOffsettable){
                std::cout<<"Funkcja "<<call->name<<" oczekuje tablicy, a dostała zmienna "<<given->val<<" w "<<current->head->name<<std::endl;
                return false;
            }
        }else{
            //We accept only arrays indexed or normal variables
            if(!given->isArray()&&varGiven->isOffsettable){
                std::cout<<"Funkcja czekuje zmiennej, a dostała tablice "<<given->val<<" w "<<current->head->name<<std::endl;
                return false;
            }
        }
    }
    return true;
}

bool Program::validateCallMain(Procedure_call* call){
        if(proceduresTable.find(call->name)==proceduresTable.end()){
        std::cout<<"Wywołanie nieznanej funkcji "<<call->name<<std::endl; 
        return false;
    }
    if(proceduresTable[call->name]->head->args->argsVec.size()!=call->args->argsVec.size()){
        std::cout<<"Nieprawidłowa ilość argumentow funkcji " <<call->name<<std::endl;
        return false;
    }
    for(int i=0; i<proceduresTable[call->name]->head->args->argsVec.size(); i++){
        Identifier* inCalled = proceduresTable[call->name]->head->args->argsVec[i];
        Identifier* given = call->args->argsVec[i];
        //std::cout<<inCalled->val<<std::endl;
        Variable* varInCalled = proceduresTable[call->name]->callableTable[inCalled->val];
        Variable* varGiven;

        if(main->symbolTable.find(given->val)!=main->symbolTable.end()){
            varGiven = main->symbolTable[given->val];
        }else{
            std::cout<<"Nieznany argument przy wywołaniu funkcji "<<call->name<<std::endl;
            return false;
        }
        if(varInCalled->isOffsettable){
            //We get indeksed array, so not array, but element of an array, so error.
            if(given->isArray()){
                std::cout<<"Funkcja "<<call->name<<" oczekuje tablicy, a dostała element tablicy "<<given->val<<std::endl;
                return false; 
            }else if(!varGiven->isOffsettable){
                std::cout<<"Funkcja "<<call->name<<" oczekuje tablicy, a dostała zmienna "<<given->val<<std::endl;
                return false;
            }
        }else{
            //We accept only arrays indexed or normal variables
            if(!given->isArray()&&varGiven->isOffsettable){
                std::cout<<"Funkcja czekuje zmiennej, a dostała tablice "<<given->val<<std::endl;
                return false;
            }
        }
    }
    return true;
}

void Program::semanticBis(){
    procedureRedeclarations();
    for(int i=0;i<procedures->procedures.size();i++){
        Procedure* current = procedures->procedures[i];
        variableRedeclaration(current);
        DFS(current);
        reset(current);
        BFS(current);
    }
    variableRedeclaration(main);
    DFS(main);
    reset(main);
    BFS(main);

    memoryManagement();

}

void Program::generateBB(){
    BBs = new BlockRepresentation();
    BBs->setBB(main->comms->head);
    for(int i=0; i<procedures->procedures.size();i++){
        BBs->addProcedureBB(procedures->procedures[i]->comms->getHead(), procedures->procedures[i]->head->name);
    }
}

void Program::printBBs(){
    std::cout<<"MAIN:\n";
    BBs->print(BBs->initialBlock);
    for(int i=0; i<procedures->procedures.size();i++){
        std::cout<<"\nPROCEDURE "<<procedures->procedures[i]->head->name<<std::endl;
        BBs->print(BBs->procedureBBs[procedures->procedures[i]->head->name]);
    }
}

bool Program::compareOffsets( Variable* a, Variable* b) {
    return a->offset < b->offset;
}

bool Program::checkOverflow(unsigned long long prevAddr, unsigned long long newAddr){
    if(prevAddr>newAddr){
        return false;
    }
    if(newAddr>MAXSIZE){
        return false;
    }
    return true;
}

void Program::memoryManagement(){
    unsigned long long memAddr=0;
    unsigned long long prevAddr=0;
    std::vector<Variable*> vars;
    for (const auto& entry : main->symbolTable) {
        vars.push_back(entry.second);
    }
    std::sort(vars.begin(), vars.end(), compareOffsets);

    //////////////MAIN MEMORY MANAGEMENT//////////////

    for(int i=0; i<vars.size();i++){
        if(checkOverflow(prevAddr, memAddr)){
            vars[i]->adress = memAddr;
            prevAddr=memAddr;
            memAddr+=1+vars[i]->offset;
        }else{
            std::cout<<"Przekroczono pamięć maszyny wirtualnej\n";
            valid= false;
        }
    }

    ///////////PROCEDURAL MEMORY MANAGEMENT///////////

    for(int i=0;i<procedures->procedures.size();i++){
        if(checkOverflow(prevAddr, memAddr)){
            procedures->procedures[i]->initialAddr = memAddr;
        }else{
            std::cout<<"Przekroczono pamięć maszyny wirtualnej\n";
            valid= false;
        }

        for(int j=0;j<procedures->procedures[i]->head->args->argsVec.size();j++){                    
            if(checkOverflow(prevAddr, memAddr)){
                std::string arg = procedures->procedures[i]->head->args->argsVec[j]->val;
                procedures->procedures[i]->callableTable[arg]->adress = memAddr;
                prevAddr = memAddr;
                memAddr++;
            }else{
                std::cout<<"Przekroczono pamięć maszyny wirtualnej\n";
                valid= false;
            }
        }

        if(checkOverflow(prevAddr, memAddr)){
            procedures->procedures[i]->retAddr = memAddr;
            prevAddr = memAddr;
            memAddr++;
        }else{
            std::cout<<"Przekroczono pamięć maszyny wirtualnej\n";
            valid= false;
        }

        std::vector<Variable*> varsProc;
        for (const auto& entry : procedures->procedures[i]->symbolTable) {
            varsProc.push_back(entry.second);
        }

        std::sort(varsProc.begin(), varsProc.end(), compareOffsets);

        for(int j=0; j<varsProc.size();j++){
            if(checkOverflow(prevAddr, memAddr)){
                varsProc[j]->adress = memAddr;
                prevAddr=memAddr;
                memAddr+=1+varsProc[j]->offset;
            }else{
                std::cout<<"Przekroczono pamięć maszyny wirtualnej\n";
                valid= false;
            }
        }
    }
}

void Program::printAdresses(){
    std::cout<<"MAIN variables:\n";
    for(auto pair : main->symbolTable){
        std::cout<<pair.first<<" -> "<<pair.second->adress<<std::endl;
    }
    for(int i=0;i<procedures->procedures.size();i++){
        std::cout<<procedures->procedures[i]->head->name<<" symbols:\n";
        for(auto pair : procedures->procedures[i]->symbolTable){
            std::cout<<pair.first<<" -> "<<pair.second->adress<<std::endl;
        }
        std::cout<<procedures->procedures[i]->head->name<<" callable:\n";
        for(auto pair : procedures->procedures[i]->callableTable){
            std::cout<<pair.first<<" -> "<<pair.second->adress<<std::endl;
        }
    }
}
