cmake_minimum_required(VERSION 3.8)
project (trikonasana)

set(lib_type SHARED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
  message("Configure for WIN32")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set(lib_type STATIC)

  set(warning_compiler_options /W3 /wd"4267" /wd"4305" /wd"4244" /wd"4996")
  # /Od disables optimization to speed compilation.
  add_compile_options(${warning_compiler_options} /MD /Od /JMC)

elseif(UNIX)
  message("Configure for LINUX")  
  SET(CMAKE_C_FLAGS "-g -Wall -std=gnu11 -O0")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")  
endif()

# trini

add_library(trini ${lib_type}
  Source/Trini/Array.c  
  Source/Trini/Vector.c  
  Source/Trini/Matrix.c  
  )

# trikonasana

add_library(engine ${lib_type}
  Source/Trikonasana/AssetLoader.c
  Source/Trikonasana/Color.c
  Source/Trikonasana/Display.c
  Source/Trikonasana/Draw.c
  Source/Trikonasana/Light.c
  Source/Trikonasana/Mesh.c
  Source/Trikonasana/Render.c
  )
target_include_directories(engine PUBLIC Source)

if (WIN32)
  target_include_directories(engine PUBLIC lib/SDL2)
  target_link_directories(engine PUBLIC lib/SDL2/lib/x64)
endif()

target_link_libraries(engine PUBLIC SDL2 SDL2_image trini)

# main

add_executable(main
  Source/Application.c  
  Source/Main.c
  )
target_include_directories(main PUBLIC Source)

if (UNIX)
  target_link_libraries(main PRIVATE engine m)
elseif(WIN32)
  target_link_libraries(main PRIVATE engine)
endif (UNIX)

# tests

add_executable(tests
  Tests/Tests.c
  )

target_include_directories(tests PUBLIC
  Tests/
  Source/
)

target_link_libraries(tests PUBLIC
  trini
)
