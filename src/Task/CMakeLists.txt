add_library(Task src/Task.cpp src/Tasks.cpp src/Todo.cpp src/Event.cpp src/Deadline.cpp)

target_include_directories(Task PUBLIC include)