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