#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <string>
#include <map>
#include <vector>
#include "fileParser.hpp"

#include <iostream>


class manipulator{
private:
  std::map<std::string, std::string> variableAndTheirValues;
public:
  bool process(std::vector<std::string> parsedValues);
  bool print(std::string string);
};

#endif
