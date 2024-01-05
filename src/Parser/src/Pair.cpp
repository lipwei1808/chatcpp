#include <iostream>
#include "Pair.h"

template <typename T, typename P>
Pair<T, P>::Pair(T first, P second): first(first), second(second) {}

template <typename T, typename P>
T Pair<T, P>::getFirst() const {
  return first;
}

template <typename T, typename P>
P Pair<T, P>::getSecond() const {
  return second;
}

template class Pair<int, int>;