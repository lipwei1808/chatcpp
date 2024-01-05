#ifndef _PAIR_H_
#define _PAIR_H_
#include <iostream>

template <typename T, typename P>
class Pair {
public:
  Pair(T first, P second);
  T getFirst() const;
  P getSecond() const;
  // TODO: Refactor this friend method definition to cpp file 
  friend std::ostream& operator<<(std::ostream& os, const Pair& other) {
    os << "{" << other.first << ": " << other.second << "}";
    return os;
  }
private:
  T first;
  P second;
};

#endif // _PAIR_H_