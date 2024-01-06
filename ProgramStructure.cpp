#include "./ProgramStructure.hpp"

bool Program::semantic(){
    bool success = true;
    for (int i = 0; i<procedures->procedures.size(); i++){
        auto& currentProcedure = *(procedures->procedures[i]);
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
            //////// MANAGE MEMORY
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

        procedures->procedures[i]->decs;
    }

    //std::vector<Identifier*>& decsVector = main->decs->decsVec;


}