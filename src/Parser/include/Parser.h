#ifndef _PARSER_H_
#define _PARSER_H_
#include <string>
#include "Instruction.h"

class Parser {
private:
  struct Input {
    std::string command;
    std::string args;
  };
  static Input parseInput(std::string s); 
public:
  static int parseInt(std::string str);
  static Instruction* parse(std::string input);
};

#endif // _PARSER_H_