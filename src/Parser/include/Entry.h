#ifndef _ENTRY_H_
#define _ENTRY_H_
#include <iostream>
#include <string>

class Entry {
public:
  Entry(std::string key, std::string value);
  std::string getKey();
  std::string getValue();
  friend std::ostream& operator << (std::ostream &out, const Entry& c);
private:
  std::string key;
  std::string value;
};

#endif // _ENTRY_H_