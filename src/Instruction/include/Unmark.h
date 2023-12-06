#ifndef _UNMARK_H_
#define _UNMARK_H_
#include "Instruction.h"
#include "Tasks.h"

class Unmark: public Instruction {
private:
  int index;
public:
  Unmark(int index);
  virtual void execute(Tasks &tasks) override;
};

#endif // _UNMARK_H_