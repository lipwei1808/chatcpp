#ifndef _LIST_H_
#define _LIST_H_
#include "Instruction.h"
#include "Tasks.h"

class List: public Instruction {
public:
  virtual void execute(Tasks &tasks) override; 
};

#endif // _LIST_H_