#include <iostream>
#include "Tasks.h"
#include "Task.h"

void Tasks::add(Task t) {
  tasks.push_back(t);
}

size_t Tasks::size() const {
  return tasks.size();
}

Task& Tasks::operator[](int idx) {
  return tasks.at(idx);
}

std::ostream &operator<<(std::ostream &os, const Tasks &tasks) {
  for (int i = 0; i < tasks.size(); i++) {
    os << "    " << i + 1 << ": " << tasks.tasks.at(i) << std::endl;
  }

  return os;
}
