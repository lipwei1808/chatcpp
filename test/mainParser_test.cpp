#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "MainParser.h"

TEST_CASE() {
  REQUIRE(MainParser::parseInt("3") == 3);
}