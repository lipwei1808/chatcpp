#include <iostream>
#include <string>
#include "Task.h"
#include "Tasks.h"

struct Input {
  std::string command;
  std::string args;
};

void printLine() {
  const std::string line = "     ----------------------";
  std::cout << line << std::endl;
}

Input parseInput(std::string s) {
  int idx = s.find(" ");
  if (idx == std::string::npos) {
    return {.command = s, .args = ""};
  }
  return {.command = s.substr(0, idx), .args = s.substr(idx, s.length())};
}

int parseArgs(std::string s) {
  return stoi(s);
}

int main() {
  Tasks tasks;
  printLine();
  std::cout << "     Hello! I'm ChatCPP" << std::endl;
  std::cout << "     What can I do for you?" << std::endl;
  printLine();
  while (true) {
    std::string input;
    getline(std::cin, input);
    printLine();
    Input parsed = parseInput(input);
    if (parsed.command == "bye") {
      break;
    }
    if (parsed.command == "list") {
      std::cout << tasks << std::endl;
      printLine();
      continue;
    }
    if (parsed.command == "mark" || parsed.command == "unmark") {
      try {
        int idx = std::stoi(parsed.args);
        if (idx == 0 || idx > tasks.size()) {
          throw std::exception();
        }
        Task &task = tasks[idx - 1];
        task.setMark(parsed.command == "mark");
        if (parsed.command == "mark") {
          std::cout << "    Nice! I've marked this task as done:" << std::endl;
        } else {
          std::cout << "    OK, I've marked this task as not done yet:" << std::endl;
        }
        std::cout << "      " << task << std::endl;
        printLine();
      } catch (std::exception e) {
        std::cout << "    Invalid index" << std::endl;
      }

      continue;
    }
    std::cout << "     added: " << input << std::endl;
    tasks.add(Task(input));
    printLine();
  }
  std::cout << "     Bye. Hope to see you again soon!" << std::endl;
  printLine();
}