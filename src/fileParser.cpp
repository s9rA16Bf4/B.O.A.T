#include "fileParser.hpp"


std::vector<std::string> file::readContent(std::string filePath){
  std::ifstream openFile(filePath);
  std::vector<std::string> toReturn;

  if (openFile.is_open()){
    std::string line = "";

    while(std::getline(openFile,line)){
      if (line[0] != '%'){ // We ignore comments
        toReturn.push_back(line);
      }
    }
    openFile.close();
  }else{ std::cerr << "Failed to open file [" << filePath << "]"<< std::endl; }
  return toReturn;
}

std::vector<std::string> file::split(std::string line, std::string delimiter){
  std::vector<std::string> toReturn;
  std::size_t delimPrev = 0, delimPos = 0;

  while(line.size() > delimPrev && line.size() > delimPos){
    delimPos = line.find(delimiter, delimPrev);
    if (delimPos == std::string::npos){ delimPos = line.size(); }
    std::string subStr = line.substr(delimPrev, delimPos-delimPrev);
    if (!subStr.empty()){ toReturn.push_back(subStr); }
    delimPrev = delimPos+delimiter.size();
  }

  return toReturn;
}
