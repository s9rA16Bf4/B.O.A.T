#ifndef BUILTINFUNC_HPP
#define BUILTINFUNC_HPP

#include <sstream>
#include "manipulator.hpp"

class builtInFunc{
public:
  bool convertIntToString(std::string variable); // Converts an int to a string
  bool convertStringToInt(std::string variable); // Converts a string to an int
};

#endif
