#include <iostream>
#include <string>
#include <ctime>
#include "Deadline.h"
#include "Add.h"
#include "DeadlineParser.h"
#include "Instruction.h"
#include "MainParser.h"
#include "ParserException.h"
#include "ArgumentParser.h"
#include "Entries.h"

Instruction* DeadlineParser::parse(std::string input) {
  MainParser::trim(input);
  if (input == "") {
    throw ParserException(Deadline::format);
  }

  std::unordered_set<std::string> keys({"when:"});
  Entries entries = ArgumentParser().parse(input, &keys);

  if (!entries.hasAllKeys() || entries.hasDuplicate({"when:"})) {
    throw ParserException(Deadline::format);
  }

  std::vector<std::string> preamble = entries.get("__preamble").value();
  std::vector<std::string> when = entries.get("when:").value();

  std::tm dt = MainParser::parseDate(when.at(0), '/');
  std::shared_ptr<Task> ptr = std::make_shared<Deadline>(Deadline(preamble.at(0), dt));

  return new Add(ptr);
}