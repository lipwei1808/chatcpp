include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(Tests test.cpp mainParser_test.cpp)

# target_include_directories(Tests PUBLIC ../src/Parser)
target_link_libraries(Tests
  Parser
  Task
  Instruction
  Catch2::Catch2WithMain
  )

add_test (NAME MyTest COMMAND Tests)