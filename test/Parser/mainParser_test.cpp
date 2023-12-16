#define CATCH_CONFIG_MAIN
#define private public
#define protected public
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "MainParser.h"
#include "Exit.h"
#include "List.h"
#include "Mark.h"
#include "Unmark.h"

template<typename T>
struct DateMatcher : Catch::Matchers::MatcherGenericBase {
    DateMatcher(T const& t):
        t{ t }
    {}
    
    bool match(T const& other) const {
      T copy = t;
      std::time_t expected = std::mktime(&copy);
      T time = MainParser::parseDate("18/08/2001", '/');
      std::time_t actual = std::mktime(&time);
      return expected == actual;
    }

    std::string describe() const override {
        return "Equals: ";
    }

private:
    T const& t;
};

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

TEST_CASE("parseDate parses valid date correctly", "[parseDate]") {
  // Setup expected
  std::tm expected = {0};
  std::istringstream is("18-08-2001");
  is >> std::get_time(&expected, "%d-%m-%Y");

  REQUIRE_THAT(expected, DateMatcher<std::tm>(MainParser::parseDate("18/08/2001", '/')));
  REQUIRE_THAT(expected, DateMatcher<std::tm>(MainParser::parseDate("18-08-2001", '-')));
  REQUIRE_THAT(expected, DateMatcher<std::tm>(MainParser::parseDate(" 18-08-2001 ", '-'))); // with whitespace
  REQUIRE_THAT(expected, DateMatcher<std::tm>(MainParser::parseDate(" \r\t18-08-2001\n ", '-'))); // with whitespaces
  REQUIRE_THAT(expected, DateMatcher<std::tm>(MainParser::parseDate("18-08-2001 other stuff", '-'))); // parses fine with other stuff
  REQUIRE_THAT(expected, !DateMatcher<std::tm>(MainParser::parseDate("19/08/2001", '/')));
  REQUIRE_THAT(expected, !DateMatcher<std::tm>(MainParser::parseDate("18/09/2001", '/')));
  REQUIRE_THAT(expected, !DateMatcher<std::tm>(MainParser::parseDate("18/08/2002", '/')));
  REQUIRE_THAT(expected, !DateMatcher<std::tm>(MainParser::parseDate("8/08/2002", '/')));
  REQUIRE_THAT(expected, !DateMatcher<std::tm>(MainParser::parseDate("18/8/2002", '/')));
}

TEST_CASE("parseDate throws exception for invalid dates", "[parseDate]") {
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("", '/')));
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("19-8-2001", '.'))); // invalid delimeter
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("19-8-2001", '/'))); // invalid delimeter
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("29/02/2023", '/'))); // leap years
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("18/13/201", '/'))); // invalid year
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("18/13/2001", '/'))); // invalid month
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("32/08/2002", '/'))); // invalid day
  REQUIRE_THROWS(DateMatcher<std::tm>(MainParser::parseDate("other stuff 18/08/2001", '/'))); // random stuff at the start
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
  REQUIRE_THROWS(dynamic_cast<Exit*>(MainParser().parse("exits")));
  REQUIRE_THROWS(dynamic_cast<Exit*>(MainParser().parse("exits")));

  REQUIRE(dynamic_cast<List*>(MainParser().parse("list")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse("list ")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse("list 4241")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse(" list 431")) != nullptr);
  REQUIRE(dynamic_cast<List*>(MainParser().parse(" list ")) != nullptr);

  REQUIRE(dynamic_cast<Mark*>(MainParser().parse("mark 4241")) != nullptr);
  REQUIRE(dynamic_cast<Mark*>(MainParser().parse(" mark 431")) != nullptr);
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse("mark a")));
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse("mark")));
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse("mark ")));
  REQUIRE_THROWS(dynamic_cast<Mark*>(MainParser().parse(" mark ")));

  REQUIRE(dynamic_cast<Unmark*>(MainParser().parse("unmark 4241")) != nullptr);
  REQUIRE(dynamic_cast<Unmark*>(MainParser().parse(" unmark 431")) != nullptr);
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse("unmark ga")));
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse("unmark")));
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse("unmark ")));
  REQUIRE_THROWS(dynamic_cast<Unmark*>(MainParser().parse(" unmark ")));
}
