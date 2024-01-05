#include <iostream>
#include "Entry.h"

Entry::Entry(std::string key, std::string value): key(key), value(value) {}

std::string Entry::getKey() {
  return key;
}

std::string Entry::getValue() {
  return value;
}

std::ostream& operator<<(std::ostream &os, const Entry& c) {
  os << "{" << c.key << ": " << c.value << "}";
  return os;
}