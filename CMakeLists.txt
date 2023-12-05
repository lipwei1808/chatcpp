cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CXX_STANDARD 11)

project(ChatCpp VERSION 1.0.0)

add_subdirectory(src/Task)

add_subdirectory(src/Parser)
add_subdirectory(src/Instruction)

add_executable(chatcpp src/main.cpp)

target_link_libraries(chatcpp Task Parser Instruction)