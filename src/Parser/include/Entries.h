#ifndef _ENTRIES_H_
#define _ENTRIES_H_
#include <unordered_map>
#include <initializer_list>
#include <string>
#include <optional>
#include <vector>
#include <unordered_set>

class Entries {
public:
  Entries(std::unordered_set<std::string>* keys = nullptr);
  void setMap(std::unordered_map<std::string, std::vector<std::string>> map);
  void addEntry(std::string key, std::string val);
  bool hasDuplicate();
  bool hasDuplicate(std::initializer_list<std::string> list);
  bool hasAllKeys();
  std::unordered_map<std::string, std::vector<std::string>> getMap();
  std::optional<std::vector<std::string>> get(std::string key);
private:
  template <typename Iterator>
  bool hasDuplicate(Iterator start, Iterator end);
private:
  std::unordered_map<std::string, std::vector<std::string>> map;
  std::unordered_set<std::string>* keys;
};

#endif // _ENTRIES_H_