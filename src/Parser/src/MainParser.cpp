#include "string"
#include "Instruction.h"
#include "MainParser.h"
#include "AddTodo.h"
#include "Exit.h"
#include "List.h"
#include "Mark.h"
#include "Unmark.h"

MainParser::Input MainParser::parseInput(std::string s) {
    int idx = s.find(" ");
    if (idx == std::string::npos) {
      return {.command = s, .args = ""};
    }
    return {.command = s.substr(0, idx), .args = s.substr(idx, s.length())};
  }

int MainParser::parseInt(std::string str) {
  return stoi(str);
}

Instruction* MainParser::parse(std::string input) {{
  Input parsed = parseInput(input);
  std::string command = parsed.command;
  if (command == "exit") {
    return new Exit;
  } else if (command == "list") {
    return new List;
  } else if (command == "mark") {
    return new Mark(parseInt(parsed.args) - 1);
  } else if (command == "unmark") {
    return new Unmark(parseInt(parsed.args) - 1);
  } 
  
  return new AddTodo(input);
}}