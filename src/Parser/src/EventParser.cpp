#include <string>
#include <ctime>
#include "Event.h"
#include "Add.h"
#include "EventParser.h"
#include "Instruction.h"
#include "MainParser.h"

Instruction* EventParser::parse(std::string input) {
  MainParser::trim(input);
  if (input == "") {
    throw std::exception();
  }

  std::vector<std::string> strings = MainParser::split(input, ' ');
  if (strings.size() != 3) {
    throw std::exception();
  }

  std::tm from = MainParser::parseDate(strings[1], '/');
  std::tm to = MainParser::parseDate(strings[2], '/');
  std::shared_ptr<Task> ptr = std::make_shared<Event>(Event(strings[0], from, to));

  return new Add(ptr);
}