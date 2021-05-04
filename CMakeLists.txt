cmake_minimum_required(VERSION 3.8)
project (boilerplate)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

SET(CMAKE_C_FLAGS "-g -Wall -std=gnu11 -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(trini SHARED
  Source/Trini/Array.c  
  Source/Trini/Vector.c  
  Source/Trini/Matrix.c  
  )

add_library(engine SHARED
  Source/Trikonasana/Application.c
  Source/Trikonasana/AssetLoader.c
  Source/Trikonasana/Color.c
  Source/Trikonasana/Display.c
  Source/Trikonasana/Draw.c
  Source/Trikonasana/Light.c
  Source/Trikonasana/Mesh.c
  Source/Trikonasana/Render.c
  )
target_include_directories(engine PUBLIC Source)
target_link_libraries(engine PUBLIC SDL2 SDL2_image trini)

add_executable(main
  Source/Main.c
  )

target_include_directories(main PUBLIC Source)
target_link_libraries(main PRIVATE engine m)
