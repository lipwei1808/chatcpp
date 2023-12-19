#ifndef _EVENT_H_
#define _EVENT_H_
#include <ctime>
#include <string>
#include "Task.h"

class Event: public Task {
public:
  Event(std::string name, std::tm to, std::tm from);
  friend std::ostream &operator<<(std::ostream& stream, const Event &event);
  virtual void print(std::ostream &os) const;
  ~Event() = default;
public:
  static std::string format;
private:
  std::tm to;
  std::tm from;
};

#endif // _EVENT_H_