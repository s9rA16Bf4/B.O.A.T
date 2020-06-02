#include "manipulator.hpp"

bool manipulator::process(std::vector<std::string> parsedValues){
  bool toReturn = false;
  file fP;

  for (std::string entry:parsedValues){
    std::vector<std::string> splitLine = fP.split(entry, " ");
    for (unsigned int i = 0; i < splitLine.size(); i++){

      if (splitLine[i] == "string" || splitLine[i] == "int" || splitLine[i] == "char"){ // new variable declarition
        variable *newVar = new variable();
        newVar->name = splitLine[i+1];
        newVar->value = splitLine[i+2];
        newVar->type = splitLine[i];

        this->variables.push_back(newVar);

      }else if (splitLine[i] == "def"){ // new function declarition
        function *newFunc = new function();
        //newFunc->functionName =
      }else if(splitLine[i] == "print"){ // Print a message
        bool result = this->print(splitLine[i+1]); // Print the messag
        toReturn = result;
      }

      else if (splitLine[i] == "+" || splitLine[i] == "-" || splitLine[i] == "*" || splitLine[i] == "/"){
        variable *A = this->find(splitLine[i-1]);
        variable *B = this->find(splitLine[i+1]);
        if (!A || !B){ std::cerr << "Error: Undeclared variable [" << ((!A)? splitLine[i-1]:splitLine[i+1]) << "]" << std::endl;}
        else if (A->type != B->type){std::cerr << "Error: Variables [" << A->name << "] and [" << B->name << "] are not of the same type" << std::endl; }
        else if (splitLine[i] == "+"){
            A->value = std::to_string(std::stoi(A->value) + std::stoi(B->value)); // add
            toReturn = true;
        }else if (splitLine[i] == "-"){
          A->value = std::to_string(std::stoi(A->value) - std::stoi(B->value)); // sub
          toReturn = true;
        }else if (splitLine[i] == "*"){
          A->value = std::to_string(std::stoi(A->value) * std::stoi(B->value)); // mult
          toReturn = true;
        }else if (splitLine[i] == "/"){
          A->value = std::to_string(std::stoi(A->value) / std::stoi(B->value)); // divide
          toReturn = true;
        }

        else{ std::cerr << "Error: Unknown operation [" << splitLine[i] << "]" << std::endl; }
      }
    }
  }
  return toReturn;
}

bool manipulator::print(std::string variableName){ // Prints the contents of a variable
  bool toReturn = false;
  variable *A = this->find(variableName);
  if (!A){
    std::cout << variableName << std::endl;
  }else{
    std::cout << A->value << std::endl;
  }
  return toReturn;
}

variable* manipulator::find(std::string varName){ // Finds the variable assocciated with varName
  variable *toReturn = nullptr;

  for (variable *entry:this->variables){
    if (entry->name == varName){
      toReturn = entry;
      break;
    }
  }

    return toReturn;
}
