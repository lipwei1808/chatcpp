#ifndef _MAIN_PARSER_H_
#define _MAIN_PARSER_H_
#include <string>
#include <ctime>
#include "Parser.h"
#include "Instruction.h"

class MainParser: public Parser {
private:
  static Input parseInput(const std::string s); 
  static std::tm parseDate(const std::string &s, char delimiter);
public:
  static int parseInt(std::string str);
  virtual Instruction* parse(std::string input);
};

#endif // _MAIN_PARSER_H_