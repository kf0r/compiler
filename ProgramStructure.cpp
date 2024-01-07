#include "./ProgramStructure.hpp"
#include <stack>
#include <iostream>


// CAN BE OPTIMIZED USING SETS BUT NOW I HAVE MORE IMPORTANT THINGS TO DO
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
            //////// MANAGE MEMORY, SET OFFSETS itd 
            currentProcedure.callableTable.insert(std::pair<std::string, Variable*> (name, var));
        }

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
                std::vector<std::string> names = top->getVars();

                for(int j=0; j<names.size();j++){
                    bool wasDeclared = false;
                    std::string name = names[j];

                    for (auto pair : currentProcedure.callableTable){
                        if(name == pair.first){
                            wasDeclared=true;
                        }
                    }

                    for (auto pair : currentProcedure.symbolTable){
                        if(name == pair.first){
                            wasDeclared=true;
                        }
                    }

                    if(!wasDeclared){
                        success=false;
                        std::cout<<"Uzycie nieznanej zmiennej "<<name<<" w "<<currentProcedure.head->name<<std::endl;
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
            std::vector<std::string> names = top->getVars();

            for(int j=0; j<names.size();j++){
                bool wasDeclared = false;
                std::string name = names[j];

                for (auto pair : main->symbolTable){
                    if(name == pair.first){
                        wasDeclared=true;
                    }
                }

                if(!wasDeclared){
                    success=false;
                    std::cout<<"Uzycie nieznanej zmiennej "<<name<<std::endl;
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