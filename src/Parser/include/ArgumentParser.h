#ifndef _ARGUMENT_PARSER_H_
#define _ARGUMENT_PARSER_H_
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Pair.h"
#include "Entries.h"

class ArgumentParser {
public:
  Entries parse(std::string input, std::unordered_set<std::string>* keys);
private:
  std::vector<Pair<int, int>> getPrefixes(
    std::string input,
    std::unordered_set<std::string>* keys
  );
  Entries getEntries(
    std::string input,
    std::unordered_set<std::string>* keys,
    const std::vector<Pair<int, int>>& prefixes
  );
};

#endif // _ARGUMENT_PARSER_H_