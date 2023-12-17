#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>
#include "Task.h"

std::string Task::getName() const {
  return name;
}

void Task::setMark(bool val) {
  marked = val;
}

bool Task::getMark() const {
  return marked;
}

void Task::print(std::ostream &os) const {
  std::string icon = marked ? "X" : " ";
  os << "[" << icon << "] " << name;
}

std::ostream &operator<<(std::ostream& os, const Task &task) {
  task.print(os);
  return os;
}

Task::~Task() = default;


std::string Task::getFormattedDateTime(std::tm dt) {
  std::ostringstream os;
  os << std::put_time(&dt, "%d/%m/%y");
  return os.str();

}