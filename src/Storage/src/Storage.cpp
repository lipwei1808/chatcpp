#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "MainParser.h"
#include "Todo.h"
#include "Event.h"
#include "Deadline.h"
#include "Storage.h"
#include "Saveable.h"
#include "Tasks.h"

static std::vector<std::string> parseFields(std::vector<std::string>::iterator start, std::vector<std::string>::iterator end) {
  std::vector<int> chars;
  for (;start != end - 1; start++) {
    chars.push_back(MainParser::parseInt(*start));
  }
  std::string dataChunk = *start;
  std::vector<std::string> res;
  
  int i = 0;
  int chunkPtr = 0;
  while (i < chars.size()) {
    int numOfChars = chars[i];
    std::string x = "";
    for (int j = chunkPtr; j < chunkPtr + numOfChars; j++) {
      x += dataChunk[j];
    }
    res.push_back(x);
    chunkPtr += numOfChars;
    i++;
  }
  return res;
}


Storage::Storage(std::string filepath): filepath(filepath) {}

std::shared_ptr<Storage> Storage::getInstance(std::string filepath) {
  if (!checkFilepath(filepath)) {
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
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(fs, line)) {
    lines.push_back(line);
  }
  fs.close();
  return Tasks(parseToTasks(lines));
}

std::shared_ptr<Task> parseToTask(std::vector<std::string>::iterator start, std::vector<std::string>::iterator end) {
  std::string task = *start;
  start++;
  if (task != "todo" && task != "deadline" && task != "event") {
    return nullptr;
  }
  std::vector<std::string> fields = parseFields(start, end);

  if (task == "todo") {
    if (fields.size() != 2) {
      return nullptr;
    }
    return std::make_shared<Todo>(Todo(fields[0]));
  } else if (task == "deadline") {
    if (fields.size() != 3) {
      return nullptr;
    }
    bool marked = fields[1] == "1";
    std::tm dt = MainParser::parseDate(fields[2], '/');
    return std::make_shared<Deadline>(Deadline(fields[0], dt, marked));
  } else if (task == "event") {
    if (fields.size() != 4) {
      return nullptr;
    }

    bool marked = fields[1] == "1";
    std::tm from = MainParser::parseDate(fields[2], '/');
    std::tm to = MainParser::parseDate(fields[3], '/');
    return std::make_shared<Event>(Event(fields[0], from, to, marked));
  }
  return nullptr;
}

std::vector<std::shared_ptr<Task>> Storage::parseToTasks(std::vector<std::string> lines) const {
  std::vector<std::shared_ptr<Task>> res;
  int i = 0;
  while (i < lines.size()) {
    std::string num = lines[i];
    i++;
    int numOfLines = MainParser::parseInt(num);
    std::shared_ptr<Task> taskPtr = parseToTask(lines.begin() + i, lines.begin() + i + numOfLines);
    if (taskPtr != nullptr) {
      res.push_back(taskPtr);
    }

    i += numOfLines;
  }
  return res;
}

std::string Storage::getFilepath() const {
  return filepath;
}

bool Storage::checkFilepath(std::string filepath) {
  if (filepath == "") {
    return false;
  }

  return true;
}