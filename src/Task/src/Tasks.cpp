#include <iostream>
#include <memory>
#include "Tasks.h"
#include "Task.h"

void Tasks::add(std::shared_ptr<Task> t) {
  tasks.push_back(t);
}

size_t Tasks::size() const {
  return tasks.size();
}

std::shared_ptr<Task> Tasks::operator[](int idx) {
  return tasks[idx];
}

std::ostream &operator<<(std::ostream &os, const Tasks &tasks) {
  for (int i = 0; i < tasks.size(); i++) {
    std::shared_ptr<Task> task = tasks.tasks.at(i);
    os << "    " << i + 1 << ": " << *task << std::endl;
  }

  return os;
}
