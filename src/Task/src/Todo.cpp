#include <string>
#include "Task.h"
#include "Todo.h"

std::string Todo::format = "todo [text] eg: todo run";

Todo::Todo(std::string name): Task(name) {}