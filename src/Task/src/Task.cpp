#include <string>
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

std::ostream &operator<<(std::ostream& os, const Task &task) {
  std::string icon = task.marked ? "X" : " ";
  os << "[" << icon << "] " << task.name;
  return os;
}

Task::~Task() = default;