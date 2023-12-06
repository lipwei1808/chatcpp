#ifndef _EXIT_H_
#define _EXIT_H_
#include <string>
#include <iostream>
#include "Tasks.h"
#include "Instruction.h"

class Exit: public Instruction {
public:
  virtual void execute(Tasks &task) override;
};

#endif // _EXIT_H