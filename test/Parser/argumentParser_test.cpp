#define private public
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include "Entries.h"
#include "Pair.h"
#include "ArgumentParser.h"

struct PrefixMatcher: Catch::Matchers::MatcherGenericBase {
public:
  PrefixMatcher(std::vector<Pair<int, int>> prefixes): prefixes(prefixes) {}
  bool match(const std::vector<Pair<int, int>> other) const {
    if (prefixes.size() != other.size()) return false;
      for (int i = 0; i < prefixes.size(); i++) {
        if (prefixes[i].getFirst() != other[i].getFirst()) return false;
        if (prefixes[i].getSecond() != other[i].getSecond()) return false;
      }

      return true;
  }
  std::string describe() const override {
      return "Equals: " + Catch::rangeToString(prefixes);;
  }

private:
  std::vector<Pair<int, int>> prefixes;
};

TEST_CASE("getPrefixes correctly returns empty vector when no prefix present", "[getPrefixes]") {
  std::string input = "todo run";
  std::vector<Pair<int, int>> prefixes = ArgumentParser().getPrefixes(input, nullptr);
  REQUIRE(prefixes.size() == 0);
}

TEST_CASE("getPrefixes correctly returns all prefixes when no keys present", "[getPrefixes]") {
  std::string input = "deadline run when: 18/08/2001";
  std::vector<Pair<int, int>> expected({Pair<int, int>(13, 17)});
  std::vector<Pair<int, int>> actual = ArgumentParser().getPrefixes(input, nullptr);
  REQUIRE_THAT(expected, PrefixMatcher(actual));

  input = "event runnig program from: 18/08/2001 to:19/08/2001";
  expected = std::vector<Pair<int, int>>({Pair<int, int>(21, 25), Pair<int, int>(38, 40)});
  actual = ArgumentParser().getPrefixes(input, nullptr);
  REQUIRE_THAT(expected, PrefixMatcher(actual));
}

TEST_CASE("getPrefixes correctly returns a map of prefixes with keys present", "[getPrefixes]") {
  SECTION("deadline") {
    std::string input = "deadline run when: 18/08/2001";

    std::unordered_set<std::string> emptyKeys;
    std::vector<Pair<int, int>> expectedEmptyKeys;
    REQUIRE_THAT(expectedEmptyKeys, PrefixMatcher(ArgumentParser().getPrefixes(input, &emptyKeys)));

    std::unordered_set<std::string> keysNotPresentInInput({""});
    std::vector<Pair<int, int>> expectedKeysNotPresentInInput;
    REQUIRE_THAT(expectedKeysNotPresentInInput, PrefixMatcher(ArgumentParser().getPrefixes(input, &keysNotPresentInInput)));

    std::unordered_set<std::string> allKeysInInput({"when:"});
    std::vector<Pair<int, int>> expectedAllKeysInInput({Pair<int, int>(13, 17)});
    REQUIRE_THAT(expectedAllKeysInInput, PrefixMatcher(ArgumentParser().getPrefixes(input, &allKeysInInput)));

    std::unordered_set<std::string> moreKeys({"when:", "hey:"});
    std::vector<Pair<int, int>> expectedMoreKeys({Pair<int, int>(13, 17)});
    REQUIRE_THAT(expectedMoreKeys, PrefixMatcher(ArgumentParser().getPrefixes(input, &moreKeys)));
  }
  
  SECTION("event") {
    std::string input = "event runnig program from: 18/08/2001 to:19/08/2001";

    std::unordered_set<std::string> allKeysInInput({"from:", "to:"});
    std::vector<Pair<int, int>> expectedAllKeysInInput = std::vector<Pair<int, int>>({Pair<int, int>(21, 25), Pair<int, int>(38, 40)});
    REQUIRE_THAT(expectedAllKeysInInput, PrefixMatcher(ArgumentParser().getPrefixes(input, &allKeysInInput)));
    
    std::unordered_set<std::string> lessKeys({"from:"});
    std::vector<Pair<int, int>> expectedLessKeys({Pair<int, int>(21, 25)});
    REQUIRE_THAT(expectedLessKeys, PrefixMatcher(ArgumentParser().getPrefixes(input, &lessKeys)));

    std::unordered_set<std::string> moreKeys({"from:", "hey:"});
    std::vector<Pair<int, int>> expectedMoreKeys({Pair<int, int>(21, 25)});
    REQUIRE_THAT(expectedMoreKeys, PrefixMatcher(ArgumentParser().getPrefixes(input, &moreKeys)));
  }
}

TEST_CASE("getEntries correctly returns entire string as preamble when no prefixes given", "[getEntries]") {
  std::string input = "event runnig program from: 18/08/2001 to:19/08/2001";
  Entries e = ArgumentParser().getEntries(input, nullptr, std::vector<Pair<int, int>>());
  std::unordered_map<std::string, std::vector<std::string>> expected({{"__preamble", std::vector<std::string>({input})}});
  REQUIRE(e.getMap() == expected);
}

TEST_CASE("getEntries correctly returns with prefix", "[getEntries]") {
  SECTION("retrieve all prefixes in input string") {
    std::string input = "event runnig program from: 18/08/2001 to:19/08/2001 check: whola ";
    std::vector<Pair<int, int>> prefixes({Pair<int, int>(21, 25), Pair<int, int>(38, 40), Pair<int, int>(52, 57)});
    std::unordered_map<std::string, std::vector<std::string>> expected({
      {"__preamble", std::vector<std::string>({"event runnig program "})},
      {"from:", std::vector<std::string>({" 18/08/2001 "})},
      {"to:", std::vector<std::string>({"19/08/2001 "})},
      {"check:", std::vector<std::string>({" whola "})}
    });
    REQUIRE(ArgumentParser().getEntries(input, nullptr, prefixes).getMap() == expected);
  }

  SECTION("retrieve some prefixes in input string") {
    std::string input = "event runnig program from: 18/08/2001 to:19/08/2001";
    std::vector<Pair<int, int>> prefixes({Pair<int, int>(21, 25)});
    std::unordered_map<std::string, std::vector<std::string>> expected({
      {"__preamble", std::vector<std::string>({"event runnig program "})},
      {"from:", std::vector<std::string>({" 18/08/2001 to:19/08/2001"})}
    });
    REQUIRE(ArgumentParser().getEntries(input, nullptr, prefixes).getMap() == expected);
  }

  SECTION("retrieve argument for last prefix in string") {
    std::string input = "event runnig program from: 18/08/2001 to:19/08/2001";
    std::vector<Pair<int, int>> prefixes({Pair<int, int>(38, 40)});
    std::unordered_map<std::string, std::vector<std::string>> expected({
      {"__preamble", std::vector<std::string>({"event runnig program from: 18/08/2001 "})},
      {"to:", std::vector<std::string>({"19/08/2001"})}
    });
    REQUIRE(ArgumentParser().getEntries(input, nullptr, prefixes).getMap() == expected);
  }
}