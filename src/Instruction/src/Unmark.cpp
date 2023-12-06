#include <iostream>
#include "Unmark.h"
#include "Tasks.h"

Unmark::Unmark(int index): index(index) {}

void Unmark::execute(Tasks &tasks) {
  if (index < 0 || index >= tasks.size()) {
    throw std::exception();
  }
  Task& task = tasks[index];
  task.setMark(false);
  std::cout << "    OK, I've marked this task as not done yet:" << std::endl;
  std::cout << "      " << task << std::endl;
}