cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(engine SHARED
  Source/Application/Application.c
  Source/Graphics/Display.c
  Source/Graphics/Draw.c
  Source/Math/Vector.c  
  )
target_include_directories(engine PUBLIC Source)
target_link_libraries(engine PUBLIC SDL2)

add_executable(main
  Source/Main.c
  )

target_include_directories(main PUBLIC Source)
target_link_libraries(main PRIVATE engine)
