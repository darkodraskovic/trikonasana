cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(main src/main.c)
target_include_directories(main PUBLIC src)
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
