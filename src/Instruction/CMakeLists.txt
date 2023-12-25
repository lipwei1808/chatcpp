add_library(Instruction src/Exit.cpp src/List.cpp src/Mark.cpp src/Unmark.cpp src/Add.cpp)

target_include_directories(Instruction PUBLIC include PUBLIC ../Task/include ../Exception/include ../Storage/include)