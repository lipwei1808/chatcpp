#ifndef _ADD_H_
#define _ADD_H_
#include <string>
#include "Tasks.h"
#include "Instruction.h"

class Add: public Instruction {
private:
  std::string input;
public:
  Add(std::string);
  virtual void execute(Tasks &tasks) override;
};

#endif // _ADD_H_