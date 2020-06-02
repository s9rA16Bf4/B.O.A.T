#include "manipulator.hpp"

bool manipulator::process(std::vector<std::string> parsedValues){
  bool toReturn = false;
  file fP;

  for (std::string entry:parsedValues){
    std::vector<std::string> splitLine = fP.split(entry, " ");
    for (unsigned int i = 0; i < splitLine.size(); i++){

<<<<<<< HEAD
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
=======
      if (splitLine[i] == "="){ this->variableAndTheirValues[splitLine[i-1]] = splitLine[i+1]; } // Create a new variable

      else if (splitLine[i] == "+" || splitLine[i] == "-" || splitLine[i] == "*" || splitLine[i] == "/"){ // we are gonna manipulate two variables
        auto variableA = this->variableAndTheirValues.find(splitLine[i-1]); // Find our two variables
        auto variableB = this->variableAndTheirValues.find(splitLine[i+1]);

        if (variableA == this->variableAndTheirValues.end() || variableB == this->variableAndTheirValues.end()){  // We did not find one of our variables
           std::cerr << "Error: Variable [" << ((variableA == this->variableAndTheirValues.end())? splitLine[i-1]:splitLine[i+1]) << "] has not been declared" << std::endl;
        }else{
          if (splitLine[i] == "+"){ // add
            variableA->second = std::to_string(std::stoi(variableA->second) + std::stoi(variableB->second));
            toReturn = true;

          }else if (splitLine[i] == "-"){ // sub
            variableA->second = std::to_string(std::stoi(variableA->second) - std::stoi(variableB->second));
            toReturn = true;

          }else if (splitLine[i] == "*"){ // multi
            variableA->second = std::to_string(std::stoi(variableA->second) * std::stoi(variableB->second));
            toReturn = true;

          }else if (splitLine[i] == "/"){ // division
            if (variableB->second != "0"){
              std::cout << variableB->second << std::endl;
              variableA->second = std::to_string(std::stoi(variableA->second) / std::stoi(variableB->second));
              toReturn = true;
            }else{
              std::cerr << "Error: Division by zero. Aborting" << std::endl;
            }
          }

        }
      }else if(splitLine[i] == "print"){
        bool result = this->print(splitLine[i+1]); // Print the messag
        toReturn = result;
      }else{
        //std::cerr << "Error: Unknown operation [" << splitLine[i] << "]" << std::endl;
      }
    }
  }
    return toReturn;
}

bool manipulator::print(std::string string){ // Prints the contents of a variable
  bool toReturn = false;
  if (string[0] == '"' && string[string.size()-1] == '"'){ // Its a string to print
    std::cout << string << std::endl; // maybe not include newline?
    toReturn = true;

  }else{ // its a variable
    auto existVariable = this->variableAndTheirValues.find(string);

    if (existVariable == this->variableAndTheirValues.end()){ std::cerr << "Error: Variable [" << string << "] has not been declared" << std::endl;}
    else{
      std::cout << existVariable->second << std::endl; // maybe not include newline?
      toReturn = true;
    }
  }

>>>>>>> f84df6c291fbe1b19617fe6f16e36c64afd2e6c3
  return toReturn;
}
