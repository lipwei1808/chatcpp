include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

file(GLOB PARSER_SOURCES Parser/*.cpp)
add_executable(Tests test.cpp ${PARSER_SOURCES})

target_link_libraries(Tests
  Parser
  Task
  Instruction
  Storage
  Catch2::Catch2WithMain
  )

add_test (NAME MyTest COMMAND Tests)