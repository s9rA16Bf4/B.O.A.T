#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <string>
#include <vector>
#include "fileParser.hpp"
#include "builtInFunc.hpp"

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

static std::vector<variable*> variables;
static std::vector<function*> functions;

class manipulator{

public:
  bool process(std::vector<std::string> parsedValues);
  bool print(std::string variableName);
  variable* find(std::string varName);
};

#endif
