#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
#include "Instruction.h"
#include "MainParser.h"
#include "TodoParser.h"
#include "DeadlineParser.h"
#include "EventParser.h"
#include "Exit.h"
#include "List.h"
#include "Mark.h"
#include "Unmark.h"

// trim from start (in place)
void MainParser::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void MainParser::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void MainParser::trim(std::string &s) {
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
  } else if (command == "todo") {
    return TodoParser().parse(parsed.args);
  } else if (command == "deadline") {
    return DeadlineParser().parse(parsed.args);
  } else if (command == "event") {
    return EventParser().parse(parsed.args);
  }

  throw std::exception();
}}

std::tm MainParser::parseDate(std::string s, char delimiter) {
  trim(s);
  std::istringstream is(s);
  int d, m, y;
  char delimeter1, delimeter2;
  if (!(is >> d >> delimeter1 >> m >> delimeter2 >> y)) {
    throw std::exception();
  }
  if (delimeter1 != delimiter || delimeter2 != delimiter) {
    throw std::exception();
  }

  // Populate tm struct with values
  std::tm dateObject {0};
  dateObject.tm_mday = d;
  dateObject.tm_mon = m - 1;
  dateObject.tm_year = y - 1900;

  // Localise to time_t and reconvert back
  std::time_t when = std::mktime(&dateObject);
  std::tm* time = std::localtime(&when);
  
  if (time->tm_mday != d || time->tm_mon + 1 != m || time->tm_year + 1900 != y) {
    throw std::exception();
  }

  return dateObject;
}

std::vector<std::string> MainParser::split(std::string s, char delimeter) {
  std::istringstream is(s);
  std::string tmp;
  std::vector<std::string> res;
  while (std::getline(is, tmp, delimeter)) {
    res.push_back(tmp);
  }

  return res;
}