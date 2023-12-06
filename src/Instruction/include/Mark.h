#ifndef _MARK_H_
#define _MARK_H_
#include "Tasks.h"
#include "Instruction.h"

class Mark: public Instruction {
private:
  int index;
public:
  Mark(int index);
  virtual void execute(Tasks &tasks) override;
};

#endif // _MARK_H_