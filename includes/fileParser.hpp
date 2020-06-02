#ifndef FILEPARSER_HPP
#define FILEPARSER_HPP

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <iostream>

class file{
public:
  std::vector<std::string> readContent(std::string filePath);
  std::vector<std::string> split(std::string string, std::string delimiter);
};

#endif
