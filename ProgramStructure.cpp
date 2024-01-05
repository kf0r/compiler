#include "./ProgramStructure.hpp"

bool Program::semantic(){
    bool success = true;
    for (int i = 0; i<procedures->procedures.size(); i++){
        auto& currentProcedure = *(procedures->procedures[i]);
        std::vector<Identifier*>& argsVector = currentProcedure.head->args->argsVec;

        for(int j=0; j<argsVector.size(); j++){
            std::string name = argsVector[j]->val;
            for (auto pair : currentProcedure.declarationTable){

                if(name == pair.first){
                    std::cout<<"Redeklaracja zmiennej "<<name<< " w "<<currentProcedure.head->name<<std::endl;
                    success = false;
                }
            }
            Variable* var = new Variable;
            var->id=name;
            //////// MANAGE MEMORY
            currentProcedure.declarationTable.insert(std::pair<std::string, Variable*> (name, var));
            
        }
    }
}