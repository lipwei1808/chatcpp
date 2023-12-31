#include <vector>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "ArgumentParser.h"

static inline std::pair<int, int> getPairFromIndex(int current, int size) {
  return std::pair<int, int>(current + 1, current + size - 1);
}

static std::vector<std::pair<int, int>> getPrefixes(
  std::string input,
  std::unordered_set<std::string> keys
) {
  std::vector<std::pair<int, int>> prefixes;
  std::regex pattern("\\s(\\S+:\\.*)");
  int current = 0;
  std::string str = input;
  for (std::smatch sm; std::regex_search(str, sm, pattern);) {
    int idx = sm.prefix().length();
    current += idx;
    int size = sm.str().length();
    std::pair<int, int> pair = getPairFromIndex(current, size);
    std::string arg = input.substr(pair.first, pair.second + 1);
    if (keys.find(arg) != keys.end()) {
      prefixes.push_back(pair);
    }
    current += size;
    str = sm.suffix();
  } 

  return prefixes;
}

static std::unordered_map<std::string, std::string> getEntries(
  std::string input,
  std::vector<std::pair<int, int>> prefixes
) {
  std::unordered_map<std::string, std::string> entries;

  for (int i = 0; i < entries.size(); i++) {
    std::pair<int, int> pair = prefixes[i];
    std::string prefix = input.substr(pair.first, pair.second + 1);
    std::string arg;
    if (i == entries.size() - 1) {
      arg = input.substr(pair.second + 1, std::string::npos);
    } else {
      arg = input.substr(pair.second + 1, prefixes[i + 1].first);
    }
    std::cout << "Prefix: " << prefix << ", Argument: " << arg << std::endl;
    entries[prefix] = arg;
  }

  return entries;
}

std::unordered_map<std::string, std::string> ArgumentParser::parse(
  std::string input,
  std::unordered_set<std::string> keys
) {
  std::vector<std::pair<int, int>> prefixes = getPrefixes(input, keys);
  return getEntries(input, prefixes);
}