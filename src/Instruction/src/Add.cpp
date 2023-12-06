#include <iostream>
#include <string>
#include "Add.h"
#include "Task.h"
#include "Tasks.h"

Add::Add(std::string input): input(input) {}

void Add::execute(Tasks &tasks) {
  tasks.add(Task(input));
  std::cout << "     added: " << input << std::endl;
}
