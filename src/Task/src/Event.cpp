#include <string>
#include <chrono>
#include "Event.h"
#include "date/date.h"

Event::Event(std::string name, date::sys_seconds date): Task(name), datetime(date) {}

std::string Event::getFormattedDateTime() {
  return "";
}