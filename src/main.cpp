#include <iostream>
#include <string>
#include "Task.h"
#include "Tasks.h"
#include "Parser.h"
#include "Instruction.h"

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

void getOpening() {
  printLine();
  std::cout << "     Hello! I'm ChatCPP" << std::endl;
  std::cout << "     What can I do for you?" << std::endl;
  printLine();
}

int main() {
  Tasks tasks;
  getOpening();

  while (true) {
    std::string input;
    getline(std::cin, input);
    printLine();
    Instruction* instruction = Parser::parse(input);
    try {
      instruction->execute(tasks);
      if (input == "exit") {
        break;
      }
    } catch (std::exception e) {
      std::cout << "    Invalid index" << std::endl;
    }
    printLine();
  }

  printLine();
}