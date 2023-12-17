#include <iostream>
#include <string>
#include <chrono>
#include "Deadline.h"
#include "Task.h"

Deadline::Deadline(std::string name, std::tm when): Task(name), when(when) {}

void Deadline::print(std::ostream &os) const {
  Task::print(os);
  os << " When: " << Deadline::getFormattedDateTime(when);
}

std::ostream &operator<<(std::ostream& os, const Deadline &deadline) {
  deadline.print(os);
  return os;
}