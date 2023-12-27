#ifndef _TASK_H_
#define _TASK_H_
#include <ctime>
#include <string>
#include <iostream>
#include "Saveable.h"

class Task: public Saveable {
private:
  std::string name;
  bool marked = false;
protected:
  static std::string getFormattedDateTime(std::tm);
public:
  Task(std::string name, bool marked = false): name(name), marked(marked) {}
  std::string getName() const;
  void setMark(bool val);
  bool getMark() const;
  friend std::ostream &operator<<(std::ostream& stream, const Task &task); 
  virtual void print(std::ostream& os) const;
  virtual ~Task() = 0;
};

#endif // _TASK_H_