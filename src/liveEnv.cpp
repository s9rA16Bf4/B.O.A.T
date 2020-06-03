#include <string>
#include <iostream>
#include "liveEnv.hpp"
#include "manipulator.hpp"

void live::liveEnv(){
  manipulator mP;
  std::string line = "";
  std::vector<std::string> commands;
  std::cout << ">> ";

  while(std::getline(std::cin, line)){
    std::cout << ">> ";

    if (line == "q"){ break; }
    else if (line == "run"){ mP.process(commands);}

    else if(line == "show"){
      for(std::string entry:commands){
        std::cout << entry << std::endl;
      }
    }else if (line == "help"){
      std::cout << "### Commands ###" << std::endl;
      std::cout << "\thelp - This window" << std::endl;
      std::cout << "\tq - Quits the live enviroment" << std::endl;
      std::cout << "\tshow  - shows all the commands that are gonna be processed when 'run' is entered" << std::endl;
      std::cout << "\tclear - removes all the commands which are supposed to be processed when 'run' is entered" << std::endl;
      std::cout << "\trun - Runs all the commands previously entered" << std::endl;
      std::cout << "\t-- Everything else entered are gonna be treated as a 'command'--" << std::endl;

    }else if(line == "clear"){ commands.clear(); }
    else{ commands.push_back(line); }
  }
}
