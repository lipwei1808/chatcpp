#include <string>
#include <vector>
#include "Entries.h"

Entries::Entries(std::vector<std::string> keys): keys(keys) {}

bool Entries::hasDuplicate() {
  return hasDuplicate(keys.begin(), keys.end());
}

bool Entries::hasDuplicate(std::initializer_list<std::string> keys) {
  // return hasDuplicate(keys.begin(), keys.end());
  return true;
}

bool Entries::hasDuplicate(const std::vector<std::string>::iterator start, const std::vector<std::string>::iterator end) {
  for (auto key = start; key != end; key++) {
    if (map.find(*key) == map.end()) {
        return false;
    }
    if (map[*key].size() > 1) {
      return false;
    }
  }
  return true;
}

bool Entries::hasAllKeys() {
  for (const std::string& key: keys) {
    if (map.find(key) == map.end()) {
      return false;
    }
  }

  return true;
}