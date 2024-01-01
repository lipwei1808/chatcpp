#define private public
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include "ArgumentParser.h"

struct PrefixMatcher: Catch::Matchers::MatcherGenericBase {
public:
  PrefixMatcher(std::vector<std::pair<int, int>> prefixes): prefixes(prefixes) {}
  bool match(const std::vector<std::pair<int, int>> other) const {
    if (prefixes.size() != other.size()) return false;
      for (int i = 0; i < prefixes.size(); i++) {
        if (prefixes[i].first != other[i].first) return false;
        if (prefixes[i].second != other[i].second) return false;
      }

      return true;
  }
  std::string describe() const override {
      return "Equals: " + Catch::rangeToString(prefixes);;
  }

private:
  std::vector<std::pair<int, int>> prefixes;
};

TEST_CASE("getPrefixes correctly returns empty map when no prefix present", "[getPrefixes]") {
  std::string input = "todo run";
  std::vector<std::pair<int, int>> prefixes = ArgumentParser().getPrefixes(input, nullptr);
  REQUIRE(prefixes.size() == 0);
}

TEST_CASE("getPrefixes correctly returns all prefixes when no keys present", "[getPrefixes]") {
  std::string input = "deadline run when: 18/08/2001";
  std::vector<std::pair<int, int>> expected({std::make_pair(13, 17)});
  std::vector<std::pair<int, int>> actual = ArgumentParser().getPrefixes(input, nullptr);
  REQUIRE_THAT(expected, PrefixMatcher(actual));

  input = "event runnig program from: 18/08/2001 to:19/08/2001";
  expected = std::vector<std::pair<int, int>>({std::make_pair(21, 25), std::make_pair(38, 40)});
  actual = ArgumentParser().getPrefixes(input, nullptr);
  REQUIRE_THAT(expected, PrefixMatcher(actual));
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