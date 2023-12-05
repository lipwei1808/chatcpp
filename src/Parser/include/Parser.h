#ifndef _PARSER_H_
#define _PARSER_H_
#include <string>
#include "Instruction.h"

class Parser {
public:
  static Instruction* parse(std::string input);
};

#endif // _PARSER_H_