#ifndef _TASKS_H_
#define _TASKS_H_
#include <vector>
#include <memory>
#include "Task.h"

// TODO: Add an iteartor so can do for (const t: Tasks)
class Tasks {
private:
public:
  std::vector<std::shared_ptr<Task>> tasks; // TODO: Refer to above
  Tasks() = default;
  Tasks(std::vector<std::shared_ptr<Task>> tasks);
  void add(std::shared_ptr<Task> t);
  size_t size() const;
  std::shared_ptr<Task> operator[](int idx);
  friend std::ostream &operator<<(std::ostream& stream, const Tasks &tasks); 
  void save();
};

#endif // _TASKS_H