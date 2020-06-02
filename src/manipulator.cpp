#include "manipulator.hpp"

bool manipulator::process(std::vector<std::string> parsedValues){
  bool toReturn = false;
  file fP;

  for (std::string entry:parsedValues){
    std::vector<std::string> splitLine = fP.split(entry, " ");
    for (unsigned int i = 0; i < splitLine.size(); i++){

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

  return toReturn;
}
