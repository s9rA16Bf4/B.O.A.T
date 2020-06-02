#include <string>
#include <iostream>
#include "liveEnv.hpp"
#include "manipulator.hpp"

void live::liveEnv(){
  manipulator mP;
  std::string line = "";
  bool run = true;
  std::vector<std::string> commands;

  while(run){
    std::cout << ">>  ";
    std::cin >> line;

    if (line == "help"){
      // Do something
    }else if (line == "q"){ run = false; }
    else if (line == "run"){ mP.process(commands); }
    else{ commands.push_back(line); }
  }
}
