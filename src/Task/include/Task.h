#ifndef _TASK_H_
#define _TASK_H_
#include <string>
#include <iostream>

class Task {
private:
  std::string name;
  bool marked = false;
public:
  Task(std::string name): name(name) {}
  std::string getName() const;
  void setMark(bool val);
  bool getMark() const;
  friend std::ostream &operator<<(std::ostream& stream, const Task &task); 
  virtual ~Task() = 0;
};

#endif // _TASK_H_