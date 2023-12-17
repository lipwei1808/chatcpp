#include <string>
#include <iostream>
#include <chrono>
#include "Event.h"
#include "Task.h"

Event::Event(std::string name, std::tm to, std::tm from): Task(name), from(from), to(to) {}

void Event::print(std::ostream &os) const {
  Task::print(os);
  os << " From: " << Event::getFormattedDateTime(from) << " To: " << Event::getFormattedDateTime(to);
}

std::ostream &operator<<(std::ostream& os, const Event &event) {
  event.print(os);
  return os;
}
