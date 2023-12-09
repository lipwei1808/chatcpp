#ifndef _PARSER_H_
#define _PARSER_H_
#include <string>
#include "Instruction.h"

class Parser {
protected:
  struct Input {
    std::string command;
    std::string args;
  };
private:
  virtual Instruction* parse(std::string input) = 0;
};

#endif // _PARSER_H_