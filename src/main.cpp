#include <iostream>
#include "Task.h"

void printLine() {
  const std::string line = "     ----------------------";
  std::cout << line << std::endl;
}

void listTasks(const std::vector<Task> &tasks) {
    for (int i = 0; i < tasks.size(); i++) {
      std::cout << "     " << i + 1 << ": " << tasks.at(i) << std::endl;
    }
}

void parseArgs(std::string s) {
  std::string token = s.substr(0, s.find(" "));
}

int main() {
  std::vector<Task> tasks;
  printLine();
  std::cout << "     Hello! I'm ChatCPP" << std::endl;
  std::cout << "     What can I do for you?" << std::endl;
  printLine();
  while (true) {
    std::string input;
    getline(std::cin, input);
    printLine();
    if (input == "bye") {
      break;
    }
    if (input == "list") {
      listTasks(tasks);
      printLine();
      continue;
    }
    std::cout << "     added: " << input << std::endl;
    tasks.push_back(Task(input));
    printLine();
  }
  std::cout << "     Bye. Hope to see you again soon!" << std::endl;
  printLine();
}