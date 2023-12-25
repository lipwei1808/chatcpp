#include <string>
#include <iostream>
#include <chrono>
#include "MainParser.h"
#include "Event.h"
#include "Task.h"

std::string Event::format = "event [text] [from date] [to date] eg: event run 18/08/2001 19/08/2001";

Event::Event(std::string name, std::tm to, std::tm from): Task(name), from(from), to(to) {}

void Event::print(std::ostream &os) const {
  Task::print(os);
  os << " From: " << Event::getFormattedDateTime(from) << " To: " << Event::getFormattedDateTime(to);
}

std::vector<std::string> Event::parse() {
  using namespace std;
  vector<string> lines;
  lines.push_back("5");
  lines.push_back(to_string(getName().length()));
  std::string marked = getMark() ? "1" : "0";
  lines.push_back(to_string(marked.length()));
  std::string fromDateString = MainParser::convertDateToString(from);
  std::string toDateString = MainParser::convertDateToString(to);
  lines.push_back(to_string(fromDateString.length()));
  lines.push_back(to_string(toDateString.length()));
  lines.push_back(getName() + marked + fromDateString + toDateString);
  return lines;
}


std::ostream &operator<<(std::ostream& os, const Event &event) {
  event.print(os);
  return os;
}
