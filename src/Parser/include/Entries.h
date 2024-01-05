#ifndef _ENTRIES_H_
#define _ENTRIES_H_
#include <unordered_map>
#include <string>
#include <optional>
#include <vector>

class Entries {
public:
  Entries() = default;
  Entries(std::vector<std::string> keys);
  void setMap(std::unordered_map<std::string, std::vector<std::string>> map);
  void addEntry(std::string key, std::string val);
  bool hasDuplicate();
  bool hasDuplicate(std::initializer_list<std::string> list);
  bool hasAllKeys();
  std::unordered_map<std::string, std::vector<std::string>> getMap();
  std::optional<std::vector<std::string>> get(std::string key);
private:
  bool hasDuplicate(const std::vector<std::string>::iterator start, const std::vector<std::string>::iterator end);
private:
  std::unordered_map<std::string, std::vector<std::string>> map;
  std::vector<std::string> keys;
};

#endif // _ENTRIES_H_