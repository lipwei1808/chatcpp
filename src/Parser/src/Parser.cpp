#include <string>
#include "Instruction.h"
#include "Parser.h"
#include "Exit.h"

Instruction* Parser::parse(std::string input) {{
  return new Exit;
}}