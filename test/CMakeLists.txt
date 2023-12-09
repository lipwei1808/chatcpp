include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(Tests test.cpp)

target_link_libraries(Tests
  Catch2::Catch2WithMain
  )
add_test (NAME MyTest COMMAND Tests)