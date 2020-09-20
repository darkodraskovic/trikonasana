cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(math SHARED
  Source/Math/Vector.c
  )
target_include_directories(math PUBLIC Source)

add_library(renderer SHARED
  Source/Renderer/Display.c
  Source/Renderer/Draw.c
  )
target_include_directories(renderer PUBLIC Source)

add_executable(main
  Source/Application.c
  Source/Main.c
  )
target_include_directories(main PUBLIC Source)
target_link_libraries(main PRIVATE SDL2 math renderer)
