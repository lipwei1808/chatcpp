#ifndef _DEADLINE_H_
#define _DEADLINE_H_
#include <ctime>
#include <string>
#include "Task.h"

class Deadline: public Task {
private:
  std::tm when;
public:
  Deadline(std::string name, std::tm when);
  friend std::ostream &operator<<(std::ostream& stream, const Deadline &deadline);
  virtual void print(std::ostream &os) const;
  ~Deadline() = default;
};

#endif // _DEADLINE_H_