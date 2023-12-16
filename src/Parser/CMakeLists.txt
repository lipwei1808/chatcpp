add_library(Parser src/MainParser.cpp src/TodoParser.cpp src/DeadlineParser.cpp src/EventParser.cpp)

target_include_directories(Parser PUBLIC ../Instruction/include)
target_link_libraries(Parser PRIVATE Instruction)
target_include_directories(Parser PUBLIC include)