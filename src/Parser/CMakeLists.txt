add_library(Parser src/MainParser.cpp)

target_include_directories(Parser PUBLIC ../Instruction/include)
target_link_libraries(Parser PRIVATE Instruction)
target_include_directories(Parser PUBLIC include)