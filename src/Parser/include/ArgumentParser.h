#ifndef _ARGUMENT_PARSER_H_
#define _ARGUMENT_PARSER_H_
#include <string>
#include <unordered_set>
#include <unordered_map>

class ArgumentParser {
public:
  std::unordered_map<std::string, std::string> parse(std::string input, std::unordered_set<std::string> keys);
};

#endif // _ARGUMENT_PARSER_H_