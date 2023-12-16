#include <string>
#include <chrono>
#include "Event.h"

Event::Event(std::string name, std::tm to, std::tm from): Task(name), from(from), to(to) {}

std::string Event::getFormattedDateTime() {
  return "";
}