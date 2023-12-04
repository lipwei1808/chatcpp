#ifndef _TASK_H_
#define _TASK_H_
#include <string>
#include <iostream>

class Task {
private:
  std::string name;
  bool marked;
public:
  Task(std::string name): name(name) {}
  std::string getName();
  void setMark(bool val);
  friend std::ostream &operator<<(std::ostream& stream, const Task &task); 
};

#endif // _TASK_H_