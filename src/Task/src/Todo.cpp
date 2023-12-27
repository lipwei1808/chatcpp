#include <vector>
#include <string>
#include "Task.h"
#include "Todo.h"

std::string Todo::format = "todo [text] eg: todo run";

Todo::Todo(std::string name, bool marked): Task(name, marked) {}

std::vector<std::string> Todo::parse() {
  using namespace std;
  vector<string> lines;
  lines.push_back("4");
  lines.push_back("todo");
  lines.push_back(to_string(getName().length()));
  std::string marked = getMark() ? "1" : "0";
  lines.push_back(to_string(marked.length()));
  lines.push_back(getName() + marked);
  return lines;
}