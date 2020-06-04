#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <string>
#include <vector>
#include <filesystem>

#include "fileParser.hpp"
#include "builtInFunc.hpp"

#include <iostream>

struct variable{
  std::string name;
  std::string value;
  std::string type;
};

struct function{
  std::string name;
  std::vector<std::string> funcGuts;
};

struct array{
  std::string name;
  std::string type;
  std::vector<std::string> guts;
};

static std::vector<variable*> variables;
static std::vector<function*> functions;
static std::vector<array*> arrays;

class manipulator{

public:
  bool process(std::vector<std::string> parsedValues);
  bool print(std::string variableName, bool newline);
  variable* find(std::string varName);
  array* findArr(std::string arrayName);
};

#endif
