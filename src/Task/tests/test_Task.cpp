#include <catch2/catch_test_macros.hpp>
#include "Task.h"

TEST_CASE("Task getName method returns the correct name", "[Task]") {
  Task task("Do laundry");
  REQUIRE(task.getName() == "Do laundry");
}

TEST_CASE("Task setMark method sets the marked flag correctly", "[Task]") {
  Task task("Buy groceries");
  task.setMark(true);
  REQUIRE(task.getMark() == true);

  task.setMark(false);
  REQUIRE(task.getMark() == false);
}
