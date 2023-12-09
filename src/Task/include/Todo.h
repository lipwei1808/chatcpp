#ifndef _TODO_H_
#define _TODO_H_
#include "string"

class Todo: public Task {
public:
  Todo(std::string name);
  ~Todo() = default;
};

#endif // _TODO_H