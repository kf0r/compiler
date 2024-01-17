#include "./ProgramStructure.hpp"
#include <stack>
#include <iostream>
#include <list>

void Program::procedureRedeclarations(){
    for(int i=0; i<procedures->procedures.size();i++){
        Procedure* current = procedures->procedures[i];
        std::string currentName = current->head->name;
        if(proceduresTable[currentName]){
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
            if(proc->symbolTable[id->val]){
                std::cout<<"Redeklaracja zmiennej "<<id->val<<" w procedurze "<<proc->head->name<<std::endl;
                valid = false;
            }else{
                insertSymbol(proc, id);
            }

        }
        }
        for(int i=0;i<proc->head->args->argsVec.size();i++){
            bool shouldInsert = true;
            Identifier* id = proc->head->args->argsVec[i];
            if(proc->symbolTable[id->val]){
                std::cout<<"Zmienna "<<id->val<<" wcześniej zadeklarowana w DEKLARACJACH w "<<proc->head->name<<std::endl;
                valid = false;
                shouldInsert = false;
            }
            if(proc->callableTable[id->val]){
                std::cout<<"Zmienna "<<id->val<<" wcześniej zadeklarowana w ARGUMENTACH w "<<proc->head->name<<std::endl;
                valid = false;
                shouldInsert = false;
            }
            if(shouldInsert){
                //insertCall(proc, id);
                 Variable* var = new Variable();
    var->id = id->val;
    if(id->isArray()){
        var->isOffsettable = true;
    }else{
        var->isOffsettable = false;
    }
    var->isInitialized = true;
    var->isUsed = true;
    std::cout<<"INSERTING "<<var->id<<std::endl;
    std::string name = id->val;
    proc->callableTable.insert(std::pair<std::string, Variable*>(var->id, var));
    if(proc->callableTable[var->id]){
        std::cout<<"INSERTed "<<var->id<<" successfully"<<std::endl;
    }
            }
        }
    }else{
        for(int i=0;i<programPart->decs->decsVec.size();i++){

            Identifier* id = programPart->decs->decsVec[i];
            if(programPart->symbolTable[id->val]){
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
            std::vector<Identifier*> identifiers = top->getVars();
            for(int i=0;i<identifiers.size();i++){
                validateVariableUsage(part, identifiers[i]);
            }
            
            if(dynamic_cast<Procedure_call*>(top)){
                validateCall(part,dynamic_cast<Procedure_call*>(top));
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
                    if(inst->getNext()[i]->visited){
                        queue.push_back(inst->getNext()[i]);
                    }
                }
            }
            if(dynamic_cast<Assignment*>(inst)){
                setInitialized(part, dynamic_cast<Assignment*>(inst)->identifier);
            }
            for(int i=0;i<inst->getVars().size();i++){
                setUsage(part,inst->getVars()[i]);
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
    std::string name = id->val;
    std::cout<<"INSERTING "<<var->id<<std::endl;
    programPart->symbolTable.insert(std::pair<std::string, Variable*>(var->id, var));
    if(programPart->symbolTable[var->id]){
        std::cout<<"INSERTed "<<var->id<<" successfully"<<std::endl;
    }
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
    std::cout<<"INSERTING "<<var->id<<std::endl;
    std::string name = id->val;
    procedure->callableTable.insert(std::pair<std::string, Variable*>(var->id, var));
    if(procedure->callableTable[var->id]){
        std::cout<<"INSERTed "<<var->id<<" successfully"<<std::endl;
    }
}

void Program::setInitialized(Program_part* part, Identifier* id){
    if(part->symbolTable[id->val]!=nullptr){
        part->symbolTable[id->val]->isInitialized=true;
    }
}

void Program::setUsage(Program_part* part, Identifier* id){
    if(part->symbolTable[id->val]!=nullptr){
        part->symbolTable[id->val]->isUsed=true;
        if(!part->symbolTable[id->val]->isInitialized){
            std::cout<<"Mozliwe niezainicjalizwanie zmiennej "<<id->val;
            if(dynamic_cast<Procedure*>(part)){
                std::cout<<" w procedurze "<< dynamic_cast<Procedure*>(part)->head->name<<std::endl;
            }else{
                std::cout<<" w MAIN\n";
            }
        }
    }
}

void Program::validateVariableUsage(Program_part* part, Identifier* identifier){
    if(dynamic_cast<Procedure*>(part)){
        Procedure* proc = dynamic_cast<Procedure*>(part);
        Variable* var = part->symbolTable[identifier->val];
        if(var==nullptr){
            var = proc->callableTable[identifier->val];
        }
        if(var==nullptr){
            std::cout<<"Uzycie nieznanej zmiennej "<<identifier->val<<" w procedurze "<<proc->head->name<<std::endl;
            valid=false;
        }else if(var->isOffsettable!=identifier->isArray()){
            std::cout<<"Nieprawidłowe uzycie tablicy "<<identifier->val<<" w procedurze "<<proc->head->name<<std::endl;
            valid=false;
        }

        if(dynamic_cast<IndentifierArrPid*>(identifier)){
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(identifier);
            std::string address = array->address;
            if(!part->symbolTable[address]&&!proc->callableTable[address]){
                valid=false;
                std::cout<<"Uzycie nieznanego adresu "<<address<<" tablicy "<<identifier->val<<" w procedurze "<<proc->head->name<<std::endl;
            }
        }
    }else{
        Variable* var = part->symbolTable[identifier->val];
        if(var==nullptr){
            std::cout<<"Uzycie nieznanej zmiennej "<<identifier->val<<" w MAIN "<<std::endl;
            valid=false;
        }else if(var->isOffsettable!=identifier->isArray()){
            std::cout<<"Nieprawidłowe uzycie tablicy "<<identifier->val<<" w MAIN "<<std::endl;
            valid=false;
        }

        if(dynamic_cast<IndentifierArrPid*>(identifier)){
            IndentifierArrPid* array = dynamic_cast<IndentifierArrPid*>(identifier);
            std::string address = array->address;
            if(!part->symbolTable[address]){
                valid=false;
                std::cout<<"Uzycie nieznanego adresu "<<address<<" tablicy "<<identifier->val<<" w MAIN "<<std::endl;
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
    if(!proceduresTable[call->name]){
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

        if(current->symbolTable[given->val]){
            varGiven = current->symbolTable[given->val];
        }else if(current->callableTable[given->val]){
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
        if(!proceduresTable[call->name]){
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
        Variable* varInCalled = proceduresTable[call->name]->callableTable[inCalled->val];
        Variable* varGiven;

        if(main->symbolTable[given->val]){
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
    variableRedeclaration(main);
    DFS(main);
    reset(main);
    BFS(main);
    for(int i=0;i<procedures->procedures.size();i++){
        Procedure* current = procedures->procedures[i];
        variableRedeclaration(current);
        DFS(current);
        reset(current);
        BFS(current);
    }
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