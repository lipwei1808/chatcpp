#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Deadline.h"
#include "MainParser.h"
#include "Task.h"

std::string Deadline::format = "deadline [text] [date] eg: deadline run 18/08/2001";

Deadline::Deadline(std::string name, std::tm when): Task(name), when(when) {}

void Deadline::print(std::ostream &os) const {
  Task::print(os);
  os << " When: " << Deadline::getFormattedDateTime(when);
}

std::vector<std::string> Deadline::parse() {
  using namespace std;
  vector<string> lines;
  lines.push_back("4");
  lines.push_back(to_string(getName().length()));
  std::string marked = getMark() ? "1" : "0";
  lines.push_back(to_string(marked.length()));
  std::string dateString = MainParser::convertDateToString(when);
  lines.push_back(to_string(dateString.length()));
  lines.push_back(getName() + marked + dateString);
  return lines;
}

std::ostream &operator<<(std::ostream& os, const Deadline &deadline) {
  deadline.print(os);
  return os;
}
