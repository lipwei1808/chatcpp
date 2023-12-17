#ifndef _TODO_PARSER_H_
#define _TODO_PARSER_H_
#include <string>
#include "Instruction.h"
#include "Parser.h"
#include "Add.h"

class TodoParser: public Parser {
public:
  Instruction* parse(std::string input) override;
  ~TodoParser() = default;
};

#endif // _TODO_PARSER_H_