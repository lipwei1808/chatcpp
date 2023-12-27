#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_
#include "Tasks.h"

class Instruction {
public:
  virtual void execute(Tasks &task) = 0;
  virtual ~Instruction() = default;
};

#endif // _INSTRUCTION_H_