#ifndef _TODO_H_
#define _TODO_H_
#include <vector>
#include <string>
#include "Task.h"

class Todo: public Task {
public:
  Todo(std::string name, bool marked = false);
  virtual std::vector<std::string> parse();
  ~Todo() = default;
public:
  static std::string format;
};

#endif // _TODO_H