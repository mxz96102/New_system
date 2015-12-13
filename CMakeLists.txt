cmake_minimum_required(VERSION 3.3)
project(New_system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(m)

set(SOURCE_FILES main.c main_functions.h)
add_executable(New_system ${SOURCE_FILES} set_functions.h sns_functions.h base.c base_functions.h Set.c base_structs.h set_structs.h sns_structs.h Sns.c cJSON.c cJSON.h)
