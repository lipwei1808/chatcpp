#include <iostream>
#include <memory>
#include "Tasks.h"
#include "Mark.h"

Mark::Mark(int index): index(index) {}

void Mark::execute(Tasks &tasks) {
  if (index < 0 || index >= tasks.size()) {
    throw std::exception();
  }
  std::shared_ptr<Task> task = tasks[index];
  task->setMark(true);
  std::cout << "    Nice! I've marked this task as done:" << std::endl;
  std::cout << "      " << *task << std::endl;
}