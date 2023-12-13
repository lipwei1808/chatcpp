#include "string"
#include "Instruction.h"
#include "MainParser.h"
#include "AddTodo.h"
#include "Exit.h"
#include "List.h"
#include "Mark.h"
#include "Unmark.h"

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

MainParser::Input MainParser::parseInput(std::string s) {
    trim(s);
    int idx = s.find(" ");
    if (idx == std::string::npos) {
      return {.command = s, .args = ""};
    }
    std::string command = s.substr(0, idx);
    std::string args = s.substr(idx, s.length());
    trim(command);
    trim(args);
    return {.command = command, .args = args};
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