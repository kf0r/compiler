#include "./ProgramStructure.hpp"
#include <stack>
#include <iostream>

bool Program::validateCallProc(Procedure_call* call, Procedure* current){
    if(!proceduresTable[call->name]){
        std::cout<<"Wywołanie nieznanej funkcji "<<call->name<<" w "<<current->head->name<<std::endl; 
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

// CAN BE OPTIMIZED USING SETS BUT NOW I HAVE MORE IMPORTANT THINGS TO DO
// MAYBE ALSO REFACTORED TO MORE SUBPROCEDURES TO BE EASIER TO MANTAIN
bool Program::semantic(){
    bool success = true;

    //////////////////////////////////////////////////////////////////////////////
    // REDECLARATION MANAGEMENT
    //////////////////////////////////////////////////////////////////////////////
    
    for (int i = 0; i<procedures->procedures.size(); i++){

        auto& currentProcedure = *(procedures->procedures[i]);
        for (auto pair : proceduresTable){
            if(currentProcedure.head->name == pair.first){
                std::cout<<"Redeklaracja procedury "<<currentProcedure.head->name<<std::endl;
                success = false;
            }
        }
        proceduresTable.insert(std::pair<std::string, Procedure*> (currentProcedure.head->name, &currentProcedure));

        std::vector<Identifier*>& argsVector = currentProcedure.head->args->argsVec;

        ///////////////////////////////////////////////
        //ARGUMENTS
        ///////////////////////////////////////////////
        for(int j=0; j<argsVector.size(); j++){
            std::string name = argsVector[j]->val;
            for (auto pair : currentProcedure.callableTable){

                if(name == pair.first){
                    std::cout<<"Redeklaracja zmiennej "<<name<< " w "<<currentProcedure.head->name<<std::endl;
                    success = false;
                }
            }
            Variable* var = new Variable;
            var->id=name;
            if(argsVector[j]->isArray()){
                var->isOffsettable=true;
            }else{
                var->isOffsettable=false;
            }
            //////// MANAGE MEMORY, SET OFFSETS itd 
            currentProcedure.callableTable.insert(std::pair<std::string, Variable*> (name, var));
        }

        ///////////////////////////////////////////////
        //DECLARATIONS
        ///////////////////////////////////////////////
        if(currentProcedure.decs!=nullptr){
            std::vector<Identifier*>& decsVector = currentProcedure.decs->decsVec;
            for(int j=0; j<decsVector.size(); j++){
                std::string name = decsVector[j]->val;
                for (auto pair : currentProcedure.callableTable){
                    if(name == pair.first){
                        std::cout<<"Redeklaracja zmiennej "<<name<< " w "<<currentProcedure.head->name<<std::endl;
                        success = false;
                    }
                }
                for (auto pair : currentProcedure.symbolTable){
                    if(name == pair.first){
                        std::cout<<"Redeklaracja zmiennej "<<name<< " w "<<currentProcedure.head->name<<std::endl;
                        success = false;
                   }
                }
                Variable* var = new Variable;
                var->id=name;
                var->offset = decsVector[j]->getOffset();
                if(decsVector[j]->isArray()){
                    var->isOffsettable=true;
                }else{
                    var->isOffsettable=false;
                }

                //////// MANAGE MEMORY 
                currentProcedure.symbolTable.insert(std::pair<std::string, Variable*> (name, var));
            }
        }

        //////////////////////////////////////////////////////////////////////////////
        // CHECKING IF ALL VARIABLES ARE DECLARED AND MANAGED CORRECTLY
        // CHECKING PROCEDURES CALL
        //////////////////////////////////////////////////////////////////////////////

        std::stack<Instruction*> instStack;
        instStack.push(currentProcedure.comms->getHead());
        while(!instStack.empty()){
            Instruction* top = instStack.top();
            instStack.pop();

            if(!top->visited){
                std::vector<Value*> identifiers = top->getVars();
                for(int j=0; j<identifiers.size();j++){
                    std::string name = identifiers[j]->val;
                    if(currentProcedure.symbolTable[name]){
                        if(currentProcedure.symbolTable[name]->isOffsettable!=identifiers[j]->isArray()){
                            success=false;
                            std::cout<<"Nieprawidlowe uzycie "<<name<<" w "<< currentProcedure.head->name<<std::endl;
                        }
                    }else if(currentProcedure.callableTable[name]){
                        if(currentProcedure.callableTable[name]->isOffsettable!=identifiers[j]->isArray()){
                            success=false;
                            std::cout<<"Nieprawidlowe uzycie "<<name<<" w "<< currentProcedure.head->name<<std::endl;
                        }
                    }else{
                        std::cout<<"Niezadeklarowana zmiena "<<name<<" w "<< currentProcedure.head->name<<std::endl;
                    }
                    if(dynamic_cast<IndentifierArrPid*>(identifiers[j])){

                        //Check if array indexes are correct. 
                        IndentifierArrPid* arr =  dynamic_cast<IndentifierArrPid*>(identifiers[j]);
                        std::string address = arr->address;
                        if(currentProcedure.symbolTable[address]){
                            if(currentProcedure.symbolTable[address]->isOffsettable){
                                success=false;
                                std::cout<<"Nieprawidlowe odwolanie sie do tablicy "<<name<<", zmienna "<<address <<" jest sama tablicą w "<< currentProcedure.head->name<<std::endl;
                            }
                        }else{
                            success=false;
                            std::cout<<"Nieprawidlowe odwolanie sie do tablicy "<<name<<", zmienna "<<address <<" nie jest zadeklarowana w "<< currentProcedure.head->name<<std::endl;
                        }
                    }
                }

                //////////////////////////////////////////////////////////////////////////////
                // CHECKING PROCEDURES CALL
                //////////////////////////////////////////////////////////////////////////////
                if(top->isCall()){
                    Procedure_call* call = dynamic_cast<Procedure_call*>(top);
                    if(!validateCallProc(call, &currentProcedure)){
                        success=false;
                    }
                }
                top->visited=true;
                //yep could be refactored to keep vector of instructions pointers but its cosmetics
                for(int j=0; j<top->getNext().size();j++){
                    if(top->getNext()[j]!=nullptr){
                        if(!top->getNext()[j]->visited){
                            instStack.push(top->getNext()[j]);
                        }
                    }
                }
            }
        }

    }

    ///////////////////////////////////////////////
    //MAIN
    ///////////////////////////////////////////////
    if(main->decs!=nullptr){
        std::vector<Identifier*>& decsVector = main->decs->decsVec;
        for(int i=0; i<decsVector.size(); i++){
            std::string name = decsVector[i]->val;
            for(auto pair : main->symbolTable){
                if(name == pair.first){
                    std::cout<<"Redeklaracja zmiennej "<<name<<std::endl;
                    success = false;
                }
            }
            Variable* var = new Variable;
            var->id=name;
            var->offset = decsVector[i]->getOffset();
            if(decsVector[i]->isArray()){
                var->isOffsettable=true;
            }else{
                var->isOffsettable=false;
            }
            //////// MANAGE MEMORY
            main->symbolTable.insert(std::pair<std::string, Variable*> (name, var));
        }
    }

    /*Maybe write function void DFS(&inst, message)? idk, it wouldnt be better, because DFS for procedures has to go through
    callableTable. But i could add callableTable in main as a empty map? Nah, i'll stay with this solution now :)*/
    std::stack<Instruction*> instStack;
    instStack.push(main->comms->getHead());
    while(!instStack.empty()){
        Instruction* top = instStack.top();
        instStack.pop();

        if(!top->visited){
            std::vector<Value*> identifiers = top->getVars();

            for(int j=0; j<identifiers.size();j++){
                bool wasDeclared = false;
                std::string name = identifiers[j]->val;

                if(!main->symbolTable[name]){
                    success=false;
                    std::cout<<"Uzycie nieznanej zmiennej "<<name<<std::endl;
                }else{
                    //Checking if variables are used correctly
                    if(main->symbolTable[name]->isOffsettable!=identifiers[j]->isArray()){
                        success=false;
                        std::cout<<"Nieprawidlowe uzycie "<<name<<std::endl;
                    }
                }
                if(dynamic_cast<IndentifierArrPid*>(identifiers[j])){
                    //Check if array indexes are correct. 
                    IndentifierArrPid* arr =  dynamic_cast<IndentifierArrPid*>(identifiers[j]);
                    std::string address = arr->address;
                    if(main->symbolTable[address]){
                        if(main->symbolTable[address]->isOffsettable){
                            success=false;
                            std::cout<<"Nieprawidlowe odwolanie sie do tablicy "<<name<<", zmienna "<<address <<" jest sama tablicą"<<std::endl;
                        }
                    }else{
                        success=false;
                        std::cout<<"Nieprawidlowe odwolanie sie do tablicy "<<name<<", zmienna "<<address <<" nie jest zadeklarowana"<<std::endl;
                    }
                }
            }
            if(top->isCall()){
                Procedure_call* call = dynamic_cast<Procedure_call*>(top);
                if(!validateCallMain(call)){
                    success=false;
                }
            }
            //VALIDATE CALLS

            top->visited=true;

            for(int j=0; j<top->getNext().size();j++){
                if(top->getNext()[j]!=nullptr){
                    if(!top->getNext()[j]->visited){
                        instStack.push(top->getNext()[j]);
                    }
                }
            }
        }
    }
}

void Program::printer(){
    std::stack<Instruction*> instStack;
    instStack.push(main->comms->getHead());
    while(!instStack.empty()){
        Instruction* top = instStack.top();
        instStack.pop();
        if(top->visited){
            std::vector<Value*> identifiers = top->getVars();
            for(int j=0; j<identifiers.size();j++){
                std::cout<<identifiers[j]->val<<std::endl;
            }
            top->visited=false;
            for(int j=0; j<top->getNext().size();j++){
                if(top->getNext()[j]!=nullptr){
                    if(top->getNext()[j]->visited){
                        instStack.push(top->getNext()[j]);
                    }
                }
            }
        }
    }
}