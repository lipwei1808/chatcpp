#include <iostream>
#include <string>
#include <ctime>
#include "Deadline.h"
#include "Add.h"
#include "DeadlineParser.h"
#include "Instruction.h"
#include "MainParser.h"
#include "ParserException.h"

Instruction* DeadlineParser::parse(std::string input) {
  MainParser::trim(input);
  if (input == "") {
    throw ParserException("no args");
  }

  std::vector<std::string> strings = MainParser::split(input, ' ');
  if (strings.size() != 2) {
    throw ParserException("invalid number of arguments");
  }

  std::tm dt = MainParser::parseDate(strings[1], '/');
  std::shared_ptr<Task> ptr = std::make_shared<Deadline>(Deadline(strings[0], dt));

  return new Add(ptr);
}