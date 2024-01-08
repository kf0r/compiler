#include "./ProgramStructure.hpp"
#include <stack>
#include <iostream>


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
                }

                //////// MANAGE MEMORY 
                currentProcedure.symbolTable.insert(std::pair<std::string, Variable*> (name, var));
            }
        }

        //////////////////////////////////////////////////////////////////////////////
        // CHECKING IF ALL VARIABLES ARE DECLARED AND MANAGED CORRECTLY
        //////////////////////////////////////////////////////////////////////////////

        std::stack<Instruction*> instStack;
        instStack.push(currentProcedure.comms->getHead());
        while(!instStack.empty()){
            Instruction* top = instStack.top();
            instStack.pop();

            if(!top->visited){
                std::vector<Value*> identifiers = top->getVars();
                //std::vector<Identifier*> identifiers = top->getIdentifiers(); //TODO

                for(int j=0; j<identifiers.size();j++){
                    bool wasDeclared = false;
                    std::string name = identifiers[j]->val;

                    // for (auto pair : currentProcedure.callableTable){
                    //     if(name == pair.first){
                    //         wasDeclared=true;
                    //     }
                    // }

                    // for (auto pair : currentProcedure.symbolTable){
                    //     if(name == pair.first){
                    //         wasDeclared=true;
                    //     }
                    // }

                    //Checking redeclarations
                    if(!currentProcedure.symbolTable[name]&&!currentProcedure.callableTable[name]){
                        success = false;
                        std::cout<<"Uzycie nieznanej zmiennej "<<name<<" w "<<currentProcedure.head->name<<std::endl;
                    }else{
                        //Checking if variables are used correctly


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

                // for (auto pair : main->symbolTable){
                //     if(name == pair.first){
                //         wasDeclared=true;
                //     }
                // }

                if(!main->symbolTable[name]){
                    success=false;
                    std::cout<<"Uzycie nieznanej zmiennej "<<name<<std::endl;
                }else{
                    //Checking if variables are used correctly
                }

            }
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