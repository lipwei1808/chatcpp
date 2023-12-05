#ifndef _EXIT_H_
#define _EXIT_H_
#include <iostream>
#include "Instruction.h"

class Exit: public Instruction {
public:
  virtual void execute() override;
};

#endif // _EXIT_H