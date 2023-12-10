#include <iostream>
#include <string>
#include "Chatcpp.h"
#include "Instruction.h"
#include "MainParser.h"
#include "Tasks.h"

void Chatcpp::printLine() {
  const std::string line = "     ----------------------";
  std::cout << line << std::endl;
}

void Chatcpp::getOpening() {
  printLine();
  std::cout << "     Hello! I'm ChatCPP" << std::endl;
  std::cout << "     What can I do for you?" << std::endl;
  printLine();
}

void Chatcpp::run() {
  Tasks tasks;
  getOpening();
  while (true) {
    std::string input;
    getline(std::cin, input);
    printLine();
    Instruction* instruction = MainParser().parse(input);
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