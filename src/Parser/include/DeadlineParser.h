#ifndef _DEADLINE_PARSER_H_
#define _DEADLINE_PARSER_H_
#include <string>
#include "Instruction.h"
#include "Parser.h"

class DeadlineParser: public Parser {
public:
  Instruction* parse(std::string input) override;
  ~DeadlineParser() = default;
};

#endif // _DEADLINE_PARSER_H_