#include <iostream>
#include <string>
#include "Chatcpp.h"
#include "ChatcppException.h"
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
    try {
      Instruction* instruction = MainParser().parse(input);
      instruction->execute(tasks);
      if (input == "exit") {
        break;
      }
    } catch (ChatcppException& e) {
      std::cout << e.what() << std::endl;
    } catch (std::exception e) {
      std::cout << "Something unexpected occured, exiting peacefully..." << std::endl;
      break;
    }
    printLine();
  }

  printLine();
}