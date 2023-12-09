#ifndef _ADD_TODO_H_
#define _ADD_TODO_H_
#include <string>
#include "Instruction.h"
#include "Tasks.h"

class AddTodo: public Instruction {
private:
  std::string input;
public:
  AddTodo(std::string);
  virtual void execute(Tasks &tasks) override;
};

#endif // _ADD_TODO_H_