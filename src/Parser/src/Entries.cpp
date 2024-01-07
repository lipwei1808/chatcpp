#include <string>
#include <optional>
#include <initializer_list>
#include <vector>
#include "Entries.h"
#include <unordered_set>

Entries::Entries(std::unordered_set<std::string>* keys): keys(keys) {}

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
  return hasDuplicate(keys->begin(), keys->end());
}

bool Entries::hasDuplicate(std::initializer_list<std::string> keys) {
  return hasDuplicate(keys.begin(), keys.end());
}

template <typename Iterator>
bool Entries::hasDuplicate(Iterator start, Iterator end) {
  for (auto key = start; key != end; key++) {
    if (map.find(*key) != map.end() && map[*key].size() > 1) {
        return true;
    }
  }
  return false;
}

bool Entries::hasAllKeys() {
  if (keys == nullptr) return true;

  for (const std::string& key: *keys) {
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