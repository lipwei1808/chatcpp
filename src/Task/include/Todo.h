#ifndef _TODO_H_
#define _TODO_H_
#include "string"
#include "Task.h"

class Todo: public Task {
public:
  Todo(std::string name);
  ~Todo() = default;
};

#endif // _TODO_H