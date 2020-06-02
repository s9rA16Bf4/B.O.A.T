#include "fileParser.hpp"
#include "manipulator.hpp"
#include "liveEnv.hpp"

int main(int argc, char** argv){
  file fP; // file parser class
  manipulator mP;
  live lv;

  if (argc > 1){ // File has been given
    std::vector<std::string> parsedValues = fP.readContent(argv[1]); // Read the contents of the file
    mP.process(parsedValues);
  }else{
    lv.liveEnv();
  }
  return 0;
}
