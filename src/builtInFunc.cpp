#include "builtInFunc.hpp"


bool builtInFunc::convertIntToString(std::string variableToFind){
  manipulator mp;
  variable *A = mp.find(variableToFind);

  if (!A){
    std::cerr << "Error: Variable [" << variableToFind << "] has not been declared" << std::endl;
    return false;
  }

  A->type = "string";

  return true;
}
