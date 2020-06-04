#include "builtInFunc.hpp"


bool builtInFunc::convertIntToString(std::string variableToFind){
  manipulator mp;
  variable *A = mp.find(variableToFind);
  bool toReturn = false;

  if (!A){std::cerr << "Error: Variable [" << variableToFind << "] has not been declared" << std::endl; }
  else{
    A->type = "string";
    toReturn = true;
  }

  return toReturn;
}

bool builtInFunc::convertStringToInt(std::string variableToFind){
  manipulator mp;
  variable *A = mp.find(variableToFind);
  bool toReturn = false;

  if (!A){ std::cerr << "Error: Variable [" << variableToFind << "] has not been declared" << std::endl; }

  int result;
  std::stringstream stream(A->value);

  if (stream >> result) {
    A->value = std::to_string(result);
    A->type = "int";
    toReturn = true;
  }
  else { std::cout << "Error: Couldn't convert the value of variable [" << A->name << "] from a string to an int" << std::endl;}


  return toReturn;
}
