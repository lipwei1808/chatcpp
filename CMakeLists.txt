cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CXX_STANDARD 11)

project(ChatCpp VERSION 1.0.0)

add_subdirectory(src/Task)
add_subdirectory(src/Parser)
add_subdirectory(src/Instruction)

enable_testing()
add_subdirectory(test)

add_executable(chatcpp src/main.cpp src/Chatcpp.cpp)

target_link_libraries(chatcpp Task Parser Instruction)