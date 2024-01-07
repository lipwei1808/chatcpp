#include <vector>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "ArgumentParser.h"
#include "Pair.h"

static inline Pair<int, int> getPairFromIndex(int current, int size) {
  return Pair<int, int>(current + 1, current + size - 1);
}

std::vector<Pair<int, int>> ArgumentParser::getPrefixes(
  std::string input,
  std::unordered_set<std::string>* keys
) {
  std::vector<Pair<int, int>> prefixes;
  std::regex pattern("\\s(\\S+:\\.*)");
  int current = 0;
  std::string str = input;
  for (std::smatch sm; std::regex_search(str, sm, pattern);) {
    int idx = sm.prefix().length();
    current += idx;
    int size = sm.str().length();
    Pair<int, int> pair = getPairFromIndex(current, size);
    std::string arg = input.substr(pair.getFirst(), size - 1);
    if (!keys || (keys->find(arg) != keys->end())) {
      prefixes.push_back(pair);
    }
    current += size;
    str = sm.suffix();
  } 

  return prefixes;
}

std::unordered_map<std::string, std::string> ArgumentParser::getEntries(
  std::string input,
  const std::vector<Pair<int, int>>& prefixes
) {
  std::unordered_map<std::string, std::string> entries;

  for (int i = 0; i < prefixes.size(); i++) {
    Pair<int, int> pair = prefixes[i];
    std::string prefix = input.substr(pair.getFirst(), pair.getSecond() - pair.getFirst() + 1);
    std::string arg;
    if (i == prefixes.size() - 1) {
      arg = input.substr(pair.getSecond() + 1);
    } else {
      arg = input.substr(pair.getSecond() + 1, prefixes[i + 1].getFirst() - pair.getSecond() - 1);
    }
    entries[prefix] = arg;
  }

  return entries;
}

std::unordered_map<std::string, std::string> ArgumentParser::parse(
  std::string input,
  std::unordered_set<std::string>* keys
) {
  std::vector<Pair<int, int>> prefixes = getPrefixes(input, keys);
  return getEntries(input, prefixes);
}