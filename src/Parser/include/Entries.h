#ifndef _ENTRIES_H_
#define _ENTRIES_H_
#include <unordered_map>
#include <string>
#include <vector>

class Entries {
public:
  Entries(std::vector<std::string> keys);
  bool hasDuplicate();
  bool hasDuplicate(std::initializer_list<std::string> list);
  bool hasDuplicate(const std::vector<std::string>::iterator start, const std::vector<std::string>::iterator end);
  bool hasAllKeys();
private:
  std::unordered_map<std::string, std::vector<std::string>> map;
  std::vector<std::string> keys;
};

#endif // _ENTRIES_H_