#ifndef _EVENT_PARSER_H_
#define _EVENT_PARSER_H_
#include <string>
#include "Instruction.h"
#include "Parser.h"

class EventParser: public Parser {
public:
  Instruction* parse(std::string input) override;
  ~EventParser() = default;
};

#endif // _EVENT_PARSER_H_