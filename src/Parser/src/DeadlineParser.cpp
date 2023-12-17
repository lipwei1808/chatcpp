#include <string>
#include <ctime>
#include "Deadline.h"
#include "Add.h"
#include "DeadlineParser.h"
#include "Instruction.h"
#include "MainParser.h"

Instruction* DeadlineParser::parse(std::string input) {
  MainParser::trim(input);
  if (input == "") {
    throw std::exception();
  }

  std::vector<std::string> strings = MainParser::split(input, ' ');
  if (strings.size() != 2) {
    throw std::exception();
  }

  std::tm dt = MainParser::parseDate(strings[1], '/');
  std::shared_ptr<Task> ptr = std::make_shared<Deadline>(Deadline(strings[0], dt));

  return new Add(ptr);
}