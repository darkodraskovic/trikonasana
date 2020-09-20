cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS})

add_executable(main
  Source/Application.c
  Source/Display.c
  Source/Draw.c
  Source/Main.c
  Source/Vector.c
  )
target_include_directories(main PUBLIC Source)
# target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(main PRIVATE SDL2)
