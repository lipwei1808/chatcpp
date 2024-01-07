#include <vector>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "ArgumentParser.h"
#include "Entries.h"
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

Entries ArgumentParser::getEntries(
  std::string input,
  std::unordered_set<std::string>* keys,
  const std::vector<Pair<int, int>>& prefixes
) {
  Entries entries(keys);
  if (prefixes.size() == 0) {
    entries.addEntry("__preamble", input);
  } else {
    entries.addEntry("__preamble", input.substr(0, prefixes[0].getFirst()));
  }

  for (int i = 0; i < prefixes.size(); i++) {
    Pair<int, int> pair = prefixes[i];
    std::string prefix = input.substr(pair.getFirst(), pair.getSecond() - pair.getFirst() + 1);
    std::string arg;
    if (i == prefixes.size() - 1) {
      arg = input.substr(pair.getSecond() + 1);
    } else {
      arg = input.substr(pair.getSecond() + 1, prefixes[i + 1].getFirst() - pair.getSecond() - 1);
    }
    entries.addEntry(prefix, arg);
  }

  return entries;
}

Entries ArgumentParser::parse(
  std::string input,
  std::unordered_set<std::string>* keys
) {
  std::vector<Pair<int, int>> prefixes = getPrefixes(input, keys);
  return getEntries(input, keys, prefixes);
}