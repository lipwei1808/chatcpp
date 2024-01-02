#ifndef _ARGUMENT_PARSER_H_
#define _ARGUMENT_PARSER_H_
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Pair.h"

class ArgumentParser {
public:
  std::unordered_map<std::string, std::string> parse(std::string input, std::unordered_set<std::string>* keys);
private:
  std::vector<Pair<int, int>> getPrefixes(
    std::string input,
    std::unordered_set<std::string>* keys
  );
  std::unordered_map<std::string, std::string> getEntries(
    std::string input,
    std::vector<Pair<int, int>>& prefixes
  );
};

#endif // _ARGUMENT_PARSER_H_