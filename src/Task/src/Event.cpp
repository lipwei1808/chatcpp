#include <string>
#include <iostream>
#include <chrono>
#include "Event.h"
#include "Task.h"

std::string Event::format = "event [text] [from date] [to date] eg: event run 18/08/2001 19/08/2001";

Event::Event(std::string name, std::tm to, std::tm from): Task(name), from(from), to(to) {}

void Event::print(std::ostream &os) const {
  Task::print(os);
  os << " From: " << Event::getFormattedDateTime(from) << " To: " << Event::getFormattedDateTime(to);
}

std::ostream &operator<<(std::ostream& os, const Event &event) {
  event.print(os);
  return os;
}
