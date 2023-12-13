#define CATCH_CONFIG_MAIN
#define private public
#define protected public
#include <catch2/catch_test_macros.hpp>
#include "MainParser.h"
#include "Exit.h"
#include "List.h"
#include "Mark.h"
#include "Unmark.h"

TEST_CASE("parseInt correctly returns integer", "[parseInt]") {
  REQUIRE(MainParser::parseInt("3") == 3);
  REQUIRE(MainParser::parseInt("-3") == -3);
  REQUIRE(MainParser::parseInt("3.0") == 3);
  REQUIRE(MainParser::parseInt("3.4") == 3);
}

TEST_CASE("parseInt throws exception on invalid string", "[parseInt]") {
  REQUIRE_THROWS(MainParser::parseInt("invalid"));
  REQUIRE_THROWS(MainParser::parseInt("x3.0"));
  REQUIRE_THROWS(MainParser::parseInt(""));
}

TEST_CASE("parseInput parses args and command word", "[parseInput]") {
  SECTION("parse one word string") {
    REQUIRE(MainParser::parseInput("exit").command == "exit");
    REQUIRE(MainParser::parseInput("exit  ").command == "exit");
    REQUIRE(MainParser::parseInput("   exit").command == "exit");
    REQUIRE(MainParser::parseInput("   exit  ").command == "exit");

    REQUIRE(MainParser::parseInput("exit").args == "");
    REQUIRE(MainParser::parseInput(" exit").args == "");
    REQUIRE(MainParser::parseInput("exit ").args == "");
    REQUIRE(MainParser::parseInput(" exit ").args == "");
  }

  SECTION("parse with more than one word") {
    SECTION("mark 3") {
      MainParser::Input x = MainParser::parseInput("mark 3");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

    SECTION(" mark 3 ") {
      MainParser::Input x = MainParser::parseInput(" mark 3 ");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

    SECTION("mark 3 ") {
      MainParser::Input x = MainParser::parseInput("mark 3 ");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

    SECTION(" mark 3") {
      MainParser::Input x = MainParser::parseInput(" mark 3");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

    SECTION("mark   3") {
      MainParser::Input x = MainParser::parseInput("mark   3");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

    SECTION("mark \n  3") {
      MainParser::Input x = MainParser::parseInput("mark \n  3");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

    SECTION("\nmark   3") {
      MainParser::Input x = MainParser::parseInput("\nmark   3");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

    SECTION("mark   3\r\n") {
      MainParser::Input x = MainParser::parseInput("mark   3\n\n");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

     SECTION("mark \n\n  3") {
      MainParser::Input x = MainParser::parseInput("mark \n\n  3");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3");
    }

     SECTION("mark \n\n  3 agag") {
      MainParser::Input x = MainParser::parseInput("mark \n\n  3 agag");
      REQUIRE(x.command == "mark");
      REQUIRE(x.args == "3 agag");
    }
  }
}


TEST_CASE("parse correctly returns instruction", "[parse]") {
  REQUIRE(dynamic_cast<Exit*>(MainParser().parse("exit")) != nullptr);
  REQUIRE(dynamic_cast<Exit*>(MainParser().parse("exit 421")) != nullptr);
  REQUIRE(dynamic_cast<Exit*>(MainParser().parse(" exit 421")) != nullptr);
  REQUIRE(dynamic_cast<Exit*>(MainParser().parse("exits")) == nullptr);

  REQUIRE(dynamic_cast<List*>(MainParser().parse("list")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse("list ")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse("list 4241")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse(" list 431")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse(" list ")) != nullptr);

  REQUIRE(dynamic_cast<Mark*>(MainParser().parse("mark 4241")) != nullptr);
  REQUIRE(dynamic_cast<Mark*>(MainParser().parse(" mark 431")) != nullptr);
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse("mark a")) == nullptr);
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse("mark")) == nullptr);
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse("mark ")) == nullptr);
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse(" mark ")) == nullptr);

  REQUIRE(dynamic_cast<Unmark*>(MainParser().parse("unmark 4241")) != nullptr);
  REQUIRE(dynamic_cast<Unmark*>(MainParser().parse(" unmark 431")) != nullptr);
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse("unmark ga")) == nullptr);
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse("unmark")) == nullptr);
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse("unmark ")) == nullptr);
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse(" unmark ")) == nullptr);
}
