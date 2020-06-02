#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <string>
<<<<<<< HEAD
=======
#include <map>
>>>>>>> f84df6c291fbe1b19617fe6f16e36c64afd2e6c3
#include <vector>
#include "fileParser.hpp"

#include <iostream>

<<<<<<< HEAD
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
=======

class manipulator{
private:
  std::map<std::string, std::string> variableAndTheirValues;
public:
  bool process(std::vector<std::string> parsedValues);
  bool print(std::string string);
>>>>>>> f84df6c291fbe1b19617fe6f16e36c64afd2e6c3
};

#endif
