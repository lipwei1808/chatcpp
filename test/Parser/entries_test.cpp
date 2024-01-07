#include <catch2/catch_test_macros.hpp>
#include "Entries.h"
#include <algorithm>

TEST_CASE("Constructor", "[Entries]") {
  REQUIRE_NOTHROW(Entries());

  REQUIRE_NOTHROW(Entries(std::vector<std::string>()));
  REQUIRE_NOTHROW(Entries(std::vector<std::string>({"mock", "data"})));
}

TEST_CASE("setMap correctly sets map", "[setMap]") {
  std::unordered_map<std::string, std::vector<std::string>> map({
    {"from", std::vector<std::string>({"test"})},
    {"to", std::vector<std::string>({"mock"})}
  });
  Entries e;
  e.setMap(map);
  REQUIRE(e.getMap() == map);

  std::unordered_map<std::string, std::vector<std::string>> map2({
    {"from", std::vector<std::string>({"test"})},
    {"to", std::vector<std::string>({"mock", "another"})}
  });
  e.setMap(map2);
  REQUIRE(e.getMap() == map2);
}

TEST_CASE("addEntry correctly adds an entry to map", "[addEntry]") {
  std::unordered_map<std::string, std::vector<std::string>> map({
    {"from", std::vector<std::string>({"test"})},
    {"to", std::vector<std::string>({"mock"})}
  });
  Entries e;
  e.setMap(map);

  // adding a value to an existing key
  e.addEntry("from", "another");
  REQUIRE(e.getMap() != map);

  map["from"].push_back("another");
  REQUIRE(e.getMap() == map);

  REQUIRE(e.get("from").has_value());
  std::vector<std::string> values = e.get("from").value();
  REQUIRE(values.size() == 2);

  // adding a new entry with a new key
  e.addEntry("new", "val");
  REQUIRE(e.get("new").has_value());
  values = e.get("new").value();
  REQUIRE(values.size() == 1);
  REQUIRE(std::find(values.begin(), values.end(), "val") != values.end());
}

TEST_CASE("hasDuplicate with no parameters check with keys field", "[hasDuplicate]") {
  SECTION("keys are present in string") {
    Entries e(std::vector<std::string>({"from:", "to:"}));
    std::unordered_map<std::string, std::vector<std::string>> map({
      {"from:", std::vector<std::string>({"test"})},
      {"to:", std::vector<std::string>({"mock"})}
    });
    e.setMap(map);
    REQUIRE(!e.hasDuplicate());

    e.addEntry("from:", "another");
    REQUIRE(e.hasDuplicate());

    map.erase("from:");
    e.setMap(map);
    REQUIRE(!e.hasDuplicate());
  }

  SECTION("some keys are in string") {
    Entries e(std::vector<std::string>({"to:"}));
    std::unordered_map<std::string, std::vector<std::string>> map({
      {"from:", std::vector<std::string>({"test", "another"})},
      {"to:", std::vector<std::string>({"mock"})}
    });
    e.setMap(map);

    REQUIRE(!e.hasDuplicate());
  }

  SECTION("more keys present in string") {
    Entries e(std::vector<std::string>({"to:", "from:", "when:"}));
    std::unordered_map<std::string, std::vector<std::string>> map({
      {"from:", std::vector<std::string>({"test", "another"})},
      {"to:", std::vector<std::string>({"mock"})}
    });
    e.setMap(map);

    REQUIRE(e.hasDuplicate());

    map.erase("from:");
    e.setMap(map);
    
    REQUIRE(!e.hasDuplicate());
  }
}

TEST_CASE("hasDuplicate with keys parameters", "[hasDuplicate]") {
  Entries e;
  std::unordered_map<std::string, std::vector<std::string>> map({
    {"from:", std::vector<std::string>({"test"})},
    {"to:", std::vector<std::string>({"mock", " anotehr"})},
    {"when:", std::vector<std::string>({"today"})}
  });
  e.setMap(map);

  // no keys
  REQUIRE(!e.hasDuplicate({}));

  // all keys
  REQUIRE(e.hasDuplicate({"from:", "to:", "when:"}));

  // partial keys
  REQUIRE(e.hasDuplicate({"from:", "to:"}));
  REQUIRE(!e.hasDuplicate({"from:", "when:"}));

  // more keys
  REQUIRE(e.hasDuplicate({"from:", "to:", "extra:"}));
  REQUIRE(!e.hasDuplicate({"from:", "when:", "extra:"}));
}

TEST_CASE("hasAllKeys correctly returns if all keys are present", "[hasAllKeys]") {
  SECTION("no keys in Entries field") {
    Entries e;
    REQUIRE(e.hasAllKeys());

    std::unordered_map<std::string, std::vector<std::string>> map({
      {"from:", std::vector<std::string>({"test"})},
      {"to:", std::vector<std::string>({"mock", " anotehr"})},
      {"when:", std::vector<std::string>({"today"})}
    });
    e.setMap(map);
    REQUIRE(e.hasAllKeys());
  }

  SECTION("keys present in Entries field") {
    Entries e(std::vector<std::string>({"from:", "to:"}));
    REQUIRE(!e.hasAllKeys());
    std::unordered_map<std::string, std::vector<std::string>> map({
      {"from:", std::vector<std::string>({"test"})},
      {"to:", std::vector<std::string>({"mock", " anotehr"})},
      {"when:", std::vector<std::string>({"today"})}
    });
    e.setMap(map);

    REQUIRE(e.hasAllKeys());

    map.erase("from:");
    e.setMap(map);
    REQUIRE(!e.hasAllKeys());
  }
}

TEST_CASE("getMap returns map", "[getMap]") {
  Entries e(std::vector<std::string>({"from:", "to:"}));
  std::unordered_map<std::string, std::vector<std::string>> map({
    {"from:", std::vector<std::string>({"test"})},
    {"to:", std::vector<std::string>({"mock", " anotehr"})},
    {"when:", std::vector<std::string>({"today"})}
  });
  e.setMap(map);
  REQUIRE(e.getMap() == map);

  map.erase("from:");
  REQUIRE(e.getMap() != map);
}

TEST_CASE("get returns vector of strings for key that is present", "[get]") {
  Entries e;
  std::unordered_map<std::string, std::vector<std::string>> map({
    {"from:", std::vector<std::string>({"test"})},
    {"to:", std::vector<std::string>({"mock", " anotehr"})},
    {"when:", std::vector<std::string>({"today"})}
  });
  e.setMap(map);

  REQUIRE(e.get("from:").value() == map["from:"]);
  REQUIRE(e.get("to:").value() == map["to:"]);
  REQUIRE(e.get("when:").value() == map["when:"]);
}

TEST_CASE("get returns empty optional for keys that is not present", "[get]") {
  Entries e;
  std::unordered_map<std::string, std::vector<std::string>> map({
    {"from:", std::vector<std::string>({"test"})},
    {"to:", std::vector<std::string>({"mock", " anotehr"})},
    {"when:", std::vector<std::string>({"today"})}
  });
  e.setMap(map);

  REQUIRE(!e.get("extra").has_value());
  REQUIRE(e.get("extra").value_or(std::vector<std::string>()).size() == 0);
}