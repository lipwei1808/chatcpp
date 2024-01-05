#include <string>
#include <optional>
#include <vector>
#include "Entries.h"

Entries::Entries(std::vector<std::string> keys): keys(keys) {}

void Entries::setMap(std::unordered_map<std::string, std::vector<std::string>> map) {
  this->map = map;
}

void Entries::addEntry(std::string key, std::string val) {
  if (map.find(key) == map.end()) {
    map[key] = std::vector<std::string>();
  }
  
  map[key].push_back(val);
}

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

std::unordered_map<std::string, std::vector<std::string>> Entries::getMap() {
  return map;
}

std::optional<std::vector<std::string>> Entries::get(std::string key) {
  if (map.find(key) == map.end()) {
    return {};
  }
  return map[key];
}