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

static std::vector<variable*> variables;

class manipulator{

public:
  bool process(std::vector<std::string> parsedValues);
  bool print(std::string variableName, bool newline);
  variable* find(std::string varName);
};

#endif
