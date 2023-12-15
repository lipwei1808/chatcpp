#ifndef _EVENT_H_
#define _EVENT_H_
#include "Task.h"
#include "date/date.h"

class Event: public Task {
private:
  date::sys_seconds datetime;
public:
  Event(std::string name, date::sys_seconds datetime);
  std::string getFormattedDateTime();
  ~Event() = default;
};

#endif // _EVENT_H_