add_library(Storage src/Storage.cpp)

target_include_directories(Storage PUBLIC include PUBLIC ../Task/include PUBLIC ../Parser/include PUBLIC ../Instruction/include)
