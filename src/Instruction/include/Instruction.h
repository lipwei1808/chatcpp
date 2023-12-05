#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

class Instruction {
public:
  virtual void execute() = 0;
};

#endif // _INSTRUCTION_H_