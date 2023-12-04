#include <iostream>

void printLine() {
  const std::string line = "     ----------------------";
  std::cout << line << std::endl;
}

void listTasks(const std::vector<std::string> &tasks) {
    for (int i = 0; i < tasks.size(); i++) {
      std::cout << "     " << i + 1 << ": " << tasks.at(i) << std::endl;
    }
}

int main() {
  std::vector<std::string> tasks;
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
    tasks.push_back(input);
    printLine();
  }
  std::cout << "     Bye. Hope to see you again soon!" << std::endl;
  printLine();
}