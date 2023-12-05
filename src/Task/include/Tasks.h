#ifndef _TASKS_H_
#define _TASKS_H_
#include <vector>
#include "Task.h"

class Tasks {
private:
  std::vector<Task> tasks;
public:
  Tasks() = default;
  void add(Task t);
  size_t size() const;
  Task &operator[](int idx);
  friend std::ostream &operator<<(std::ostream& stream, const Tasks &tasks); 
};

#endif // _TASKS_H