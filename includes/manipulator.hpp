#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <string>
#include <vector>
#include "fileParser.hpp"

#include <iostream>

struct variable{
  std::string name;
  std::string value;
  std::string type;
};

struct function{
  std::string functionName;
  std::string functionReturnType;
};

class manipulator{
private:
  std::vector<variable*> variables;
  std::vector<function*> functions;
public:
  bool process(std::vector<std::string> parsedValues);
  bool print(std::string variableName);
  variable* find(std::string varName);
};

#endif
