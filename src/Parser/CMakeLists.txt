add_library(Parser src/MainParser.cpp src/TodoParser.cpp src/DeadlineParser.cpp src/EventParser.cpp)

target_include_directories(Parser PUBLIC include PUBLIC ../Instruction/include PUBLIC ../Exception/include PUBLIC ../Task/include)