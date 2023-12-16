#ifndef _MAIN_PARSER_H_
#define _MAIN_PARSER_H_
#include <string>
#include <vector>
#include <ctime>
#include "Parser.h"
#include "Instruction.h"

class MainParser: public Parser {
private:
  static Input parseInput(const std::string s); 
  static void ltrim(std::string &s);
  static void rtrim(std::string &s);
public:
  static std::tm parseDate(std::string s, char delimiter);
  static std::vector<std::string> split(std::string s, char delimeter);
  static int parseInt(std::string str);
  static void trim(std::string &s);
  virtual Instruction* parse(std::string input);
};

#endif // _MAIN_PARSER_H_