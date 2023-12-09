#include <string>
#include <iostream>
#include <memory>
#include "Tasks.h"
#include "Task.h"
#include "AddTodo.h"
#include "Todo.h"

AddTodo::AddTodo(std::string input): input(input) {}

void AddTodo::execute(Tasks &tasks) {
  std::shared_ptr<Task> task = std::make_shared<Task>(Task(input));
  tasks.add(task);
  std::cout << "    added: " << input << std::endl;
}

