#include <string>
#include <chrono>
#include "Deadline.h"

Deadline::Deadline(std::string name, std::tm when): Task(name), when(when) {}

std::string Deadline::getFormattedDateTime() {
  return "";
}