#include <string>
#include "Instruction.h"
#include "Parser.h"
#include "MainParser.h"

class TodoParser: public Parser {
public:
  Instruction* parser(std::string input) {
    int idx = MainParser::parseInt(input);
  }
};