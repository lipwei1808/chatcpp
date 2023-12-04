cmake_minimum_required(VERSION 3.0.0)

project(ChatCpp VERSION 1.0.0)

file(GLOB_RECURSE chatcppSources src/*.cpp src/*.h)
add_executable(chatcpp ${chatcppSources})