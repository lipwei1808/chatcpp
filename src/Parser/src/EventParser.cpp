#include <string>
#include <ctime>
#include <unordered_set>
#include "Event.h"
#include "Add.h"
#include "EventParser.h"
#include "ArgumentParser.h"
#include "ParserException.h"
#include "Instruction.h"
#include "MainParser.h"

Instruction* EventParser::parse(std::string input) {
  MainParser::trim(input);
  if (input == "") {
    throw ParserException(Event::format);
  }

  std::unordered_set<std::string> keys({"from:", "to:"});
  Entries entries = ArgumentParser().parse(input, &keys);

  if (!entries.hasAllKeys() || entries.hasDuplicate({"from:", "to:"})) {
    throw ParserException(Event::format);
  }

  std::vector<std::string> preamble = entries.get("__preamble").value();
  std::vector<std::string> from = entries.get("from:").value();
  std::vector<std::string> to = entries.get("to:").value();

  std::tm fromDt = MainParser::parseDate(from.at(0), '/');
  std::tm toDt = MainParser::parseDate(to.at(0), '/');
  std::shared_ptr<Task> ptr = std::make_shared<Event>(Event(preamble.at(0), fromDt, toDt));

  return new Add(ptr);
}