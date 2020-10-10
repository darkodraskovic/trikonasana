cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(trini SHARED
  Source/Trini/Vector.c  
  )

add_library(engine SHARED
  Source/Trikonasana/Application.c
  Source/Trikonasana/Display.c
  Source/Trikonasana/Draw.c
  Source/Trikonasana/Mesh.c
  )
target_include_directories(engine PUBLIC Source)
target_link_libraries(engine PUBLIC SDL2 trini)

add_executable(main
  Source/Main.c
  )

target_include_directories(main PUBLIC Source)
target_link_libraries(main PRIVATE engine)
