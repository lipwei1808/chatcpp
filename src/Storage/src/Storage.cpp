#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "Storage.h"
#include "Saveable.h"
#include "Tasks.h"

Storage::Storage(std::string filepath): filepath(filepath) {}

std::shared_ptr<Storage> Storage::getInstance(std::string filepath) {
  if (filepath == "") {
    return nullptr;
  }

  // TODO: Read why cant do std::make_shared<Storage>(filepath);
  return std::make_shared<Storage>(Storage(filepath));
}

void Storage::save(Saveable &item) const {
  std::ofstream myfile;
  myfile.open (filepath, std::fstream::in | std::fstream::out | std::fstream::app);
  std::vector<std::string> lines = item.parse();
  for (std::string &s: lines) {
    myfile << s << std::endl;
  }
  myfile.close();
}

Tasks Storage::load() const {
  std::ifstream fs(filepath);
  std::vector<std::vector<std::string>> lines;
  std::string line;
  while (std::getline(fs, line)) {
    std::stringstream is(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(is, token, ',')) {
      tokens.push_back(token);
    }
    lines.push_back(tokens);
  }
  fs.close();

  for (auto &tokens: lines) {
    for (auto &s: tokens) {
      std::cout << s << std::endl;
    }
  }
  return Tasks();
}

std::string Storage::getFilepath() const {
  return filepath;
}

void Storage::checkFilepath() {}