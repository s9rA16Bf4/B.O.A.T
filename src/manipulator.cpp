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
          if (splitLine.size() == 3){
            variable *A = this->find(splitLine[i+1]);
            if (!A){
              variable *newVar = new variable();
              newVar->name = splitLine[i+1];
              newVar->type = splitLine[i];

              if (splitLine[i+2][0] == '/'){ // variable!
                std::string variableName = splitLine[i+2];
                variableName.erase(0,1); // Removes the /

                variable *B = this->find(variableName); // Find the variable

                if (!B){ std::cerr << "("<< y+1 <<") Error: variable [" << variableName<< "] has not been declared" << std::endl; }
                else{
                  if (B->type == newVar->type){ newVar->value = B->value;}
                  else{ std::cerr << "("<< y+1 <<") Error: variable [" << variableName << "] has not the same type as the one you're trying to declare" << std::endl; }
                }
              }else{ newVar->value = splitLine[i+2]; }

              variables.push_back(newVar);
            }else{ std::cerr << "("<< y+1 <<") Error: variable [" << splitLine[i+1] << "] has already been declared" << std::endl; }
          }
          else{ // array declarition
            array *newArray = new array();
            newArray->type = splitLine[i];
            newArray->name = splitLine[i+1];
          //  array* A = this->find()
            for (i = i+2; i < splitLine.size(); i++){ newArray->guts.push_back(splitLine[i]); }
            arrays.push_back(newArray);
          }


        }else if(splitLine[i] == "print" || splitLine[i] == "printnl"){ // Print a message
          bool newLine = false;
          if (splitLine[i] == "printnl"){ newLine = true; }

          for (unsigned int i = 1; i < splitLine.size(); i++){
            toReturn = this->print(splitLine[i], newLine);
            this->print(" ", newLine);
          }
          this->print("\n", newLine);

        }else if(splitLine[i] == "cits"){ toReturn = bif.convertIntToString(splitLine[i+1]); } // Convert an int to a string
        else if(splitLine[i] == "csti"){ toReturn = bif.convertStringToInt(splitLine[i+1]); } // convert a string to an int
        else if (splitLine[i] == "def"){ // new function!
          function *newFunc = new function();
          newFunc->name = splitLine[i+1];
          for (unsigned int x = i+2; x < splitLine.size(); x++){
            newFunc->funcGuts.push_back(splitLine[x]);
          }
          functions.push_back(newFunc);
          break;
        }
        else if (splitLine[i] == "+" || splitLine[i] == "-" || splitLine[i] == "*" || splitLine[i] == "/" || splitLine[i] == "//"){ // manipulation!
          variable *A = this->find(splitLine[i-1]); // Find our variables
          variable *B = this->find(splitLine[i+1]);

          if (!A || !B){ std::cerr << "("<< y+1 <<") Error: Undeclared variable [" << ((!A)? splitLine[i-1]:splitLine[i+1]) << "]" << std::endl;}
          else if (A->type != B->type){std::cerr << "("<< y+1 <<") Error: Variables [" << A->name << "] and [" << B->name << "] are not of the same type" << std::endl; }

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
            break;

          }else if (splitLine[i] == "//"){
            if (A->type == "int"){
              A->value = std::to_string(std::stoi(A->value) % std::stoi(B->value)); // modulos
              toReturn = true;
            }

          }else{ std::cerr << "("<< y+1 <<") Error: Unknown operator [" << splitLine[i] << "]" << std::endl; }

        }else if (splitLine[i] == "include"){ // include contents from another file
          if (std::filesystem::exists(splitLine[i+1])){
            std::ifstream openFile(splitLine[i+1]);
            std::string line;
            std::vector<std::string> tempVector;

            for (unsigned int x = y+1; x < parsedValues.size(); x++){ tempVector.push_back(parsedValues[x]); } // Remember our old lines

            parsedValues.resize(y); // Shrink our vector
            parsedValues.shrink_to_fit(); // resize

            while(std::getline(openFile, line)){ parsedValues.push_back(line); } // Insert the new lines

            for(std::string oldLines:tempVector){parsedValues.push_back(oldLines); } // Insert the old lines

            y--; // Jump one line up so that we can read our newly inserted values

          }else{ std::cerr << "("<< y+1 <<") Error: File [" << splitLine[i+1] << "] does not exist" << std::endl; }

        }else if (splitLine[i] == "up"){
          std::string firstPart = splitLine[i+1], secondPart = splitLine[i+2];

          if (firstPart[firstPart.size()-1] == ']' && secondPart[secondPart.size()-1] != ']'){ // We are updating an array with the contents of a vector
            std::string string = firstPart;

            int leftWingPos = string.find("[");
            int rightWingPos = string.find("]");
            std::string index = string.substr(leftWingPos+1, string.size()-1);
            int indexInt = std::stoi(index); // This will be the actual index of the array
            string = string.erase(leftWingPos, rightWingPos); // Now we have the array name
            array *A = this->findArr(string);
            variable *B = this->find(secondPart);

            if (indexInt > A->guts.size() || indexInt < 0){std::cout << "Error: index is out of bounds!" << std::endl;}
            else{
              if (!A || !B){ std::cerr << "("<< y+1 <<") Error: Undeclared variable/array [" << ((!A)? string:secondPart) << "]" << std::endl;}
              else if (A->type != B->type){std::cerr << "("<< y+1 <<") Error: Array [" << A->name << "] and variable [" << B->name << "] are not of the same type" << std::endl; }
              else{ A->guts[indexInt] = B->value; }
            }

          }else if (secondPart[secondPart.size()-1] == ']' && firstPart[splitLine[i+1].size()-1] != ']'){ // We are updating a variable with the contents of an array
            std::string string = secondPart;

            int leftWingPos = string.find("[");
            int rightWingPos = string.find("]");
            std::string index = string.substr(leftWingPos+1, string.size()-1);
            int indexInt = std::stoi(index); // This will be the actual index of the array
            string = string.erase(leftWingPos, rightWingPos); // Now we have the array name
            variable *A = this->find(firstPart);
            array *B = this->findArr(string);

            if (indexInt > B->guts.size() || indexInt < 0){std::cout << "Error: index is out of bounds!" << std::endl;}
            else{
              if (!A || !B){ std::cerr << "("<< y+1 <<") Error: Undeclared variable/array [" << ((!A)? firstPart:string) << "]" << std::endl;}
              else if (A->type != B->type){std::cerr << "("<< y+1 <<") Error: Array [" << A->name << "] and variable [" << B->name << "] are not of the same type" << std::endl; }
              else{ A->value = B->guts[indexInt]; }
            }
          }else if (secondPart[secondPart.size()-1] == ']' && firstPart[splitLine[i+1].size()-1] == ']'){ // Array to an array
            std::string string = firstPart;
            std::string string2 = secondPart;

            int leftWingPos = string.find("[");
            int rightWingPos = string.find("]");

            int leftWingPos2 = string2.find("[");
            int rightWingPos2 = string2.find("]");

            std::string index = string.substr(leftWingPos+1, string.size()-1);
            int indexInt = std::stoi(index); // This will be the actual index of the array
            string = string.erase(leftWingPos, rightWingPos); // Now we have the array name

            std::string index2 = string2.substr(leftWingPos2+1, string2.size()-1);
            int indexInt2 = std::stoi(index2); // This will be the actual index of the array
            string2 = string2.erase(leftWingPos2, rightWingPos2); // Now we have the array name

            array *A = this->findArr(string);
            array *B = this->findArr(string2);

            if (indexInt > B->guts.size() || indexInt < 0 || indexInt2 > A->guts.size() || indexInt2 < 0){std::cout << "Error: index is out of bounds!" << std::endl;}
            else{
              if (!A || !B){ std::cerr << "("<< y+1 <<") Error: Undeclared array/s [" << ((!A)? string:string2) << "]" << std::endl;}
              else if (A->type != B->type){std::cerr << "("<< y+1 <<") Error: The arrays [" << A->name << "] and [" << B->name << "] are not of the same type" << std::endl; }
              else{ A->guts[indexInt] = B->guts[indexInt2]; }
            }

          }else{
            variable *A = this->find(splitLine[i+1]); // Find our variables
            variable *B = this->find(splitLine[i+2]);
            if (!A || !B){ std::cerr << "("<< y+1 <<") Error: Undeclared variable [" << ((!A)? splitLine[i-1]:splitLine[i+1]) << "]" << std::endl;}
            else if (A->type != B->type){std::cerr << "("<< y+1 <<") Error: Variables [" << A->name << "] and [" << B->name << "] are not of the same type" << std::endl; }
            else{ A->value = B->value; }
          }

        }else if (splitLine[i] == "in"){
          variable *A = this->find(splitLine[i+1]); // Find our variables
          if (!A){ std::cerr << "("<< y+1 <<") Error: Undeclared variable [" << splitLine[i+1] << "]" << std::endl;}
          else if (A->type != "string"){std::cerr << "("<< y+1 <<") Error: Variables [" << A->name << "] is not a string" << std::endl; }
          else{ std::cin >> A->value; }

        }else if (splitLine[i] == "while"){
          variable *floor = this->find(splitLine[i+1]);
          variable *roof = this->find(splitLine[i+3]);
          if (!floor || !roof){ std::cerr << "("<< y+1 <<") Error: Undeclared variable [" << ((!floor)? splitLine[i+1]:splitLine[i+3]) << "]" << std::endl;}
          else if (floor->type != roof->type){std::cerr << "("<< y+1 <<") Error: Variables [" << floor->name << "] and [" << roof->name << "] are not of the same type" << std::endl; }
          else{
            int start = std::stoi(floor->value);
            int max = std::stoi(roof->value);
            std::string whatToDo = splitLine[i+2];
            std::string whileLine = "";

            std::vector<std::string> whileGuts;
            for (i = i+4; i < splitLine.size(); i++){ whileLine += splitLine[i] + " "; }
            whileGuts.push_back(whileLine);

            if (whatToDo == "<"){
              while(start < max){
                this->process(whileGuts);
                floor->value = std::to_string(std::stoi(floor->value)+1);
                start++;
              }
            }else if (whatToDo == ">"){
              while(start > max){
                this->process(whileGuts);
                roof->value = std::to_string(std::stoi(roof->value)-1);
                max--;
              }
            }
          }
        }else if (splitLine[i] == "if"){
          std::string firstPart = splitLine[i+1];
          std::string secondPart = splitLine[i+3];
          if (firstPart[firstPart.size()-1] == ']' && secondPart[secondPart.size()-1] != ']'){
            variable *B = this->find(secondPart);

            int leftWingPos = firstPart.find("[");
            int rightWingPos = firstPart.find("]");

            std::string index = firstPart.substr(leftWingPos+1, firstPart.size()-1);
            int indexInt = std::stoi(index); // This will be the actual index of the array

            firstPart = firstPart.erase(leftWingPos, rightWingPos); // Now we have the array name
            array *A = this->findArr(firstPart);

            if (!A || !B){ std::cout << "Error: Undeclared array [" << firstPart << "] and/or variable [" << secondPart << "]" << std::endl; }
            else{
              if (indexInt > A->guts.size() || 0 > indexInt){ std::cout << "Error: index is out of bounds!" << std::endl; }
              else{
                std::string whatToDo = splitLine[i+2];
                std::string ifLine = "";

                std::vector<std::string> ifGuts;
                for (i = i+4; i < splitLine.size(); i++){ ifLine += splitLine[i] + " "; }
                ifGuts.push_back(ifLine);

                if (whatToDo == "<=" && A->guts[indexInt] <= B->value){ this->process(ifGuts); }
                else if (whatToDo == "<" && A->guts[indexInt] < B->value){ this->process(ifGuts); }
                else if (whatToDo == ">=" && A->guts[indexInt] >= B->value){ this->process(ifGuts); }
                else if (whatToDo == ">" && A->guts[indexInt] > B->value){ this->process(ifGuts); }
                else if (whatToDo == "==" && A->guts[indexInt] == B->value){this->process(ifGuts); }
              }
            }
          }else if (firstPart[firstPart.size()-1] == ']' && secondPart[secondPart.size()-1] == ']'){

            int leftWingPos = firstPart.find("[");
            int rightWingPos = firstPart.find("]");

            int leftWingPos2 = secondPart.find("[");
            int rightWingPos2 = secondPart.find("]");


            std::string index = firstPart.substr(leftWingPos+1, firstPart.size()-1);
            int indexInt = std::stoi(index); // This will be the actual index of the array

            std::string index2 = secondPart.substr(leftWingPos2+1, secondPart.size()-1);
            int indexInt2 = std::stoi(index2); // This will be the actual index of the array

            firstPart = firstPart.erase(leftWingPos, rightWingPos); // Now we have the array name
            secondPart = secondPart.erase(leftWingPos2, rightWingPos2); // Now we have the array name

            array *A = this->findArr(firstPart);
            array *B = this->findArr(secondPart);

            if (!A || !B){ std::cout << "Error: Undeclared array/s [" << secondPart << "] and [" << firstPart << "]" << std::endl; }
            else{
              if (indexInt > A->guts.size() || 0 > indexInt){ std::cout << "Error: index is out of bounds!" << std::endl; }
              else{

                std::string whatToDo = splitLine[i+2];
                std::string ifLine = "";

                std::vector<std::string> ifGuts;
                for (i = i+4; i < splitLine.size(); i++){ ifLine += splitLine[i] + " "; }
                ifGuts.push_back(ifLine);

                if (whatToDo == "<=" && A->guts[indexInt] <= B->guts[indexInt2]){ this->process(ifGuts); }
                else if (whatToDo == "<" && A->guts[indexInt] < B->guts[indexInt2]){ this->process(ifGuts); }
                else if (whatToDo == ">=" && A->guts[indexInt] >= B->guts[indexInt2]){ this->process(ifGuts); }
                else if (whatToDo == ">" && A->guts[indexInt] > B->guts[indexInt2]){ this->process(ifGuts); }
                else if (whatToDo == "==" && A->guts[indexInt] == B->guts[indexInt2]){this->process(ifGuts); }
              }
            }

          }else if (firstPart[firstPart.size()-1] != ']' && secondPart[secondPart.size()-1] == ']'){
            variable *B = this->find(firstPart);

            int leftWingPos = secondPart.find("[");
            int rightWingPos = secondPart.find("]");

            std::string index = secondPart.substr(leftWingPos+1, secondPart.size()-1);
            int indexInt = std::stoi(index); // This will be the actual index of the array

            secondPart = secondPart.erase(leftWingPos, rightWingPos); // Now we have the array name
            array *A = this->findArr(secondPart);

            if (!A || !B){ std::cout << "Error: Undeclared array [" << secondPart << "] and/or variable [" << firstPart << "]" << std::endl; }
            else{
              if (indexInt > A->guts.size() || 0 > indexInt){ std::cout << "Error: index is out of bounds!" << std::endl; }
              else{
                std::string whatToDo = splitLine[i+2];
                std::string ifLine = "";

                std::vector<std::string> ifGuts;
                for (i = i+4; i < splitLine.size(); i++){ ifLine += splitLine[i] + " "; }
                ifGuts.push_back(ifLine);

                if (whatToDo == "<=" && A->guts[indexInt] <= B->value){ this->process(ifGuts); }
                else if (whatToDo == "<" && A->guts[indexInt] < B->value){ this->process(ifGuts); }
                else if (whatToDo == ">=" && A->guts[indexInt] >= B->value){ this->process(ifGuts); }
                else if (whatToDo == ">" && A->guts[indexInt] > B->value){ this->process(ifGuts); }
                else if (whatToDo == "==" && A->guts[indexInt] == B->value){this->process(ifGuts); }
              }
            }
          }else{
            variable *A = this->find(splitLine[i+1]);
            variable *B = this->find(splitLine[i+3]);
            if (!A || !B){ std::cerr << "("<< y+1 <<") Error: Undeclared variable [" << ((!A)? splitLine[i+1]:splitLine[i+3]) << "]" << std::endl;}
            else if (A->type != B->type){std::cerr << "("<< y+1 <<") Error: Variables [" << A->name << "] and [" << B->name << "] are not of the same type" << std::endl; }
            else{
              std::string whatToDo = splitLine[i+2];
              std::string ifLine = "";

              std::vector<std::string> ifGuts;
              for (i = i+4; i < splitLine.size(); i++){ ifLine += splitLine[i] + " "; }
              ifGuts.push_back(ifLine);

              if (whatToDo == "<=" && A->value <= B->value){ this->process(ifGuts); }
              else if (whatToDo == "<" && A->value < B->value){ this->process(ifGuts); }
              else if (whatToDo == ">=" && A->value >= B->value){ this->process(ifGuts); }
              else if (whatToDo == ">" && A->value > B->value){ this->process(ifGuts); }
              else if (whatToDo == "==" && A->value == B->value){this->process(ifGuts); }
            }
          }
          variable *A = this->find(splitLine[i+1]);
          variable *B = this->find(splitLine[i+3]);
          if (!A || !B){ std::cerr << "("<< y+1 <<") Error: Undeclared variable [" << ((!A)? splitLine[i+1]:splitLine[i+3]) << "]" << std::endl;}
          else if (A->type != B->type){std::cerr << "("<< y+1 <<") Error: Variables [" << A->name << "] and [" << B->name << "] are not of the same type" << std::endl; }
          else{
            std::string whatToDo = splitLine[i+2];
            std::string ifLine = "";

            std::vector<std::string> ifGuts;
            for (i = i+4; i < splitLine.size(); i++){ ifLine += splitLine[i] + " "; }
            ifGuts.push_back(ifLine);

            if (whatToDo == "<=" && A->value <= B->value){ this->process(ifGuts); }
            else if (whatToDo == "<" && A->value < B->value){ this->process(ifGuts); }
            else if (whatToDo == ">=" && A->value >= B->value){ this->process(ifGuts); }
            else if (whatToDo == ">" && A->value > B->value){ this->process(ifGuts); }
            else if (whatToDo == "==" && A->value == B->value){this->process(ifGuts); }
          }
        }
        else{ // might it perhaps be a func??
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
                break;
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
  if (string[0] == '/' && string[string.size()-1] != ']'){ // "Derefrence" of a variable
    string = string.erase(0, 1);

    variable *A = this->find(string);
    if (!A){ std::cout << "Error: Undeclared variable [" << string << "]"<< std::endl; }
    else{
      if (newline){ std::cout << A->value << std::endl;}
      else{std::cout << A->value;}
      toReturn = true;
    }
  }else if (string[string.size()-1] == ']' && string[0] == '/'){ // "Derefrence" of an array
    string = string.erase(0, 1); // Remove the /

    int leftWingPos = string.find("[");
    int rightWingPos = string.find("]");

    std::string index = string.substr(leftWingPos+1, string.size()-1);
    int indexInt = std::stoi(index); // This will be the actual index of the array


    string = string.erase(leftWingPos, rightWingPos); // Now we have the array name

    array *A = this->findArr(string);
    if (!A){ std::cout << "Error: Undeclared array [" << string << "]"<< std::endl; }
    else{
      if (indexInt > A->guts.size() || 0 > indexInt){ std::cout << "Error: index is out of bounds!" << std::endl; }
      else{
        if (newline){ std::cout << A->guts[indexInt] << std::endl;}
        else{std::cout << A->guts[indexInt];}
        toReturn = true;
      }
    }
  }
  else{
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

array* manipulator::findArr(std::string arrayName){ // Finds the array assocciated with arrayName
  array *toReturn = nullptr;
  for (array *entry:arrays){
    if (entry->name == arrayName){
      toReturn = entry;
      break;
    }
  }
  return toReturn;
}
