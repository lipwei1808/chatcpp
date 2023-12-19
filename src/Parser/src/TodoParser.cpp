#include <string>
#include <memory>
#include "Todo.h"
#include "TodoParser.h"
#include "Instruction.h"
#include "Add.h"
#include "MainParser.h"
#include "ParserException.h"

Instruction* TodoParser::parse(std::string input) {
  MainParser::trim(input);
  if (input == "") {
    throw ParserException(Todo::format);
  }
  std::shared_ptr<Task> ptr = std::make_shared<Todo>(Todo(input));
  return new Add(ptr);
}