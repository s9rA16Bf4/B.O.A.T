#include "manipulator.hpp"

bool manipulator::process(std::vector<std::string> parsedValues){
  bool toReturn = false;
  file fP;
  builtInFunc bif;

  for (unsigned int y = 0; y < parsedValues.size(); y++){
    std::vector<std::string> splitLine = fP.split(parsedValues[y], " ");
    for (unsigned int i = 0; i < splitLine.size(); i++){

      if (splitLine[i] != "%"){ // ignore the line if its a comment
        if (splitLine[i] == "string" || splitLine[i] == "int"){ // new variable declarition
          variable *newVar = new variable();
          newVar->name = splitLine[i+1];
          newVar->value = splitLine[i+2];
          newVar->type = splitLine[i];

          variables.push_back(newVar);

        }else if(splitLine[i] == "print" || splitLine[i] == "printnl"){ // Print a message
          bool newLine = false;
          if (splitLine[i] == "printnl"){ newLine = true; }

          for (unsigned int i = 1; i < splitLine.size(); i++){
            toReturn = this->print(splitLine[i], newLine);
            toReturn = this->print(" ", newLine);
          }

          this->print("\n", newLine);

        }else if(splitLine[i] == "cits"){ // convert a int to a string
          bool result = bif.convertIntToString(splitLine[i+1]);
          toReturn = result;

        }else if (splitLine[i] == "def"){ // new function!
          function *newFunc = new function();
          newFunc->name = splitLine[i+1];
          for (unsigned int x = i+2; x < splitLine.size(); x++){
            newFunc->funcGuts.push_back(splitLine[x]);
          }
          functions.push_back(newFunc);
          break;
        }

        else if (splitLine[i] == "+" || splitLine[i] == "-" || splitLine[i] == "*" || splitLine[i] == "/" || splitLine[i] == "//"){
          variable *A = this->find(splitLine[i-1]); // Find our variables
          variable *B = this->find(splitLine[i+1]);

          if (!A || !B){ std::cerr << "Error: Undeclared variable [" << ((!A)? splitLine[i-1]:splitLine[i+1]) << "]" << std::endl;}
          else if (A->type != B->type){std::cerr << "Error: Variables [" << A->name << "] and [" << B->name << "] are not of the same type" << std::endl; }

          else if (splitLine[i] == "+"){
            if (A->type == "int"){
              A->value = std::to_string(std::stoi(A->value) + std::stoi(B->value)); // int add
              toReturn = true;
            }else{
              A->value +=  B->value; // string add
              toReturn = true;
            }

          }else if (splitLine[i] == "-"){
            if (A->type == "int"){
              A->value = std::to_string(std::stoi(A->value) - std::stoi(B->value)); // sub
              toReturn = true;
            }

          }else if (splitLine[i] == "*"){
            if (A->type == "int"){
              A->value = std::to_string(std::stoi(A->value) * std::stoi(B->value)); // mult
              toReturn = true;
            }

          }else if (splitLine[i] == "/"){
            if (A->type == "int"){
              A->value = std::to_string(std::stof(A->value) / std::stof(B->value)); // divide
              toReturn = true;
            }

          }else if (splitLine[i] == "//"){
            if (A->type == "int"){
              A->value = std::to_string(std::stoi(A->value) % std::stoi(B->value)); // modulos
              toReturn = true;
            }

          }else{ std::cerr << "Error: Unknown operator [" << splitLine[i] << "]" << std::endl; }

        }else if (splitLine[i] == "include"){
          if (std::filesystem::exists(splitLine[i+1])){
            std::ifstream openFile(splitLine[i+1]);
            std::string line;
            std::vector<std::string> tempVector;

            for (unsigned int x = y+1; x < parsedValues.size(); x++){ tempVector.push_back(parsedValues[x]); } // Remember our old lines

            parsedValues.resize(y); // Shrink our vector
            parsedValues.shrink_to_fit(); // resize

            while(std::getline(openFile, line)){ parsedValues.push_back(line); } // Insert the new lines

            for(std::string oldLines:tempVector){ parsedValues.push_back(oldLines); } // Insert the old lines

            y = 0; // Reset

          }else{ std::cerr << "Error: File [" << splitLine[i+1] << "] does not exist" << std::endl; }

        }else{ // might it perhaps be a func???
          for (function* funcs:functions){
            if (funcs->name == splitLine[i]){
              std::vector<std::string> tempVector;
              for (unsigned int x = y+1; x < parsedValues.size(); x++){ tempVector.push_back(parsedValues[x]); } // Remember our old lines

              parsedValues.resize(y); // Shrink our vector
              parsedValues.shrink_to_fit(); // resize

              std::string functionLine = "";
              for(std::string newLine:funcs->funcGuts){ functionLine += newLine + " ";} // Create the function line from its guts
              parsedValues.push_back(functionLine);

              for(std::string oldLines:tempVector){ parsedValues.push_back(oldLines); } // Insert the old lines

              y--; // Jump one line up so that we can read our newly inserted function
            }
          }
        }
      }
    }
  }
  return toReturn;
}

bool manipulator::print(std::string string, bool newline){ // Prints the contents of a variable
  bool toReturn = false;
  if (string[0] == '/'){
    string = string.erase(0, 1);
    variable *A = this->find(string);
    if (!A){
      std::cout << "Error: Undeclared variable [" << string << "]"<< std::endl;
    }else{
      if (newline){ std::cout << A->value << std::endl;}
      else{std::cout << A->value;}
      toReturn = true;
    }
  }else{
    if (newline){ std::cout << string << std::endl; }
    else{ std::cout << string; }
    toReturn = true;
  }
  return toReturn;
}

variable* manipulator::find(std::string varName){ // Finds the variable assocciated with varName
  variable *toReturn = nullptr;
  for (variable *entry:variables){
    if (entry->name == varName){
      toReturn = entry;
      break;
    }
  }
  return toReturn;
}
