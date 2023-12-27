#include <iostream>
#include <memory>
#include "Storage.h"
#include "Tasks.h"
#include "Task.h"

Tasks::Tasks(std::vector<std::shared_ptr<Task>> tasks): tasks(tasks) {}

void Tasks::add(std::shared_ptr<Task> t) {
  tasks.push_back(t);
}

size_t Tasks::size() const {
  return tasks.size();
}

std::shared_ptr<Task> Tasks::operator[](int idx) {
  return tasks[idx];
}

void Tasks::save() {
  std::shared_ptr<Storage> s = Storage::getInstance("text.txt");
  for (const std::shared_ptr<Task> t: tasks) {
    s->save(*t);
  }
}

std::ostream &operator<<(std::ostream &os, const Tasks &tasks) {
  for (int i = 0; i < tasks.size(); i++) {
    std::shared_ptr<Task> task = tasks.tasks.at(i);
    os << "    " << i + 1 << ": " << *task << std::endl;
  }

  return os;
}