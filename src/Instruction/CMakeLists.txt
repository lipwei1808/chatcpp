add_library(Instruction src/Exit.cpp src/List.cpp src/Mark.cpp src/Unmark.cpp src/AddTodo.cpp)

target_include_directories(Instruction PUBLIC ../Task/include)
target_link_directories(Instruction PRIVATE Task)
target_include_directories(Instruction PUBLIC include)