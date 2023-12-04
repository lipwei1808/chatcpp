#include <string>
#include <iostream>
#include "Task.h"

std::string Task::getName() {
  return name;
}

void Task::setMark(bool val) {
  marked = val;
}

std::ostream &operator<<(std::ostream& os, const Task &task) {
  std::string icon = task.marked ? "X" : " ";
  os << "[" << icon << "] " << task.name << std::endl;
  return os;
}