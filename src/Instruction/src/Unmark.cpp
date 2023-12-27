#include <iostream>
#include <memory>
#include "Unmark.h"
#include "Tasks.h"
#include "InstructionException.h"

Unmark::Unmark(int index): index(index) {}

void Unmark::execute(Tasks &tasks) {
  if (index < 0 || index >= tasks.size()) {
    throw InstructionException();
  }
  std::shared_ptr<Task> task = tasks[index];
  task->setMark(false);
  tasks.save();
  std::cout << "    OK, I've marked this task as not done yet:" << std::endl;
  std::cout << "      " << *task << std::endl;
}