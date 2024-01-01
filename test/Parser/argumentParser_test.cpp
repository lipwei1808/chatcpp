#define private public
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include "ArgumentParser.h"

TEST_CASE("getPrefixes correctly returns empty map when no prefix present", "[getPrefixes]") {
  std::string input = "todo run";

  std::vector<std::pair<int, int>> prefixes = ArgumentParser().getPrefixes(input, nullptr);
  REQUIRE(prefixes.size() == 0);
}

// TEST_CASE("getPrefixes correctly returns a map of prefixes", "[getPrefixes]") {
//   std::vector<std::pair<std::string, std::vector<std::pair<int, int>>>> cases;
//   cases.push_back(
//     std::make_pair(
//       "deadline take a walk when: 18/08/2001",
//       std::vector<std::pair<int, int>>({{"when:", " 18/08/2001"}})
//     )
//   );
//   cases.push_back(
//     std::make_pair(
//       "deadline take a walk when:18/08/2001",
//       std::vector<std::pair<int, int>>({{"when:", "18/08/2001"}})
//     )
//   );
//   cases.push_back(
//     std::make_pair(
//       "event project meeting from:18/08/2001 to: 19/08/2001",
//       std::vector<std::pair<int, int>>({{"from:", "18/08/2001"}, {"to:", " 19/08/2001"}})
//     )
//   );

//   for (const auto& c: cases) {
//     std::vector<std::pair<int, int>> entries = ArgumentParser().getPrefixes(c.first, nullptr);
//     REQUIRE(c.second == entries);
//   }
// }