#ifndef _SAVEABLE_H_
#define _SAVEABLE_H_
#include <string>
#include <vector>

class Saveable {
public:
  virtual std::vector<std::string> parse() = 0;
};

#endif // _SAVEABLE_H_