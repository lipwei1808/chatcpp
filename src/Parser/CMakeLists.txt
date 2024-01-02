add_library(
  Parser
  src/Pair.cpp
  src/MainParser.cpp
  src/TodoParser.cpp 
  src/DeadlineParser.cpp 
  src/EventParser.cpp 
  src/ArgumentParser.cpp 
  src/Entries.cpp 
  src/Entry.cpp 
)

target_include_directories(Parser PUBLIC include PUBLIC ../Instruction/include PUBLIC ../Exception/include PUBLIC ../Task/include ../Storage/include)