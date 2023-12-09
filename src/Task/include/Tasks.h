#ifndef _TASKS_H_
#define _TASKS_H_
#include <vector>
#include <memory>
#include "Task.h"

class Tasks {
private:
  std::vector<std::shared_ptr<Task>> tasks;
public:
  Tasks() = default;
  void add(std::shared_ptr<Task> t);
  size_t size() const;
  std::shared_ptr<Task> operator[](int idx);
  friend std::ostream &operator<<(std::ostream& stream, const Tasks &tasks); 
};

#endif // _TASKS_H