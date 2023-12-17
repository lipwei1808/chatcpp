#ifndef _ADD_H_
#define _ADD_H_
#include <string>
#include <memory>
#include "Task.h"
#include "Instruction.h"
#include "Tasks.h"

class Add: public Instruction {
private:
  std::shared_ptr<Task> toAdd;
public:
  Add(std::shared_ptr<Task> toAdd);
  virtual void execute(Tasks &tasks) override;
};

#endif // _ADD_H_