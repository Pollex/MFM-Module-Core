cmake_minimum_required(VERSION 3.11)

project(mfmmod)


if(DEFINED AVR)
  # Default ATTiny814 speed
  add_compile_definitions(F_CPU=2666666L)
  get_filename_component(C_COMPILER_DIR ${CMAKE_C_COMPILER} DIRECTORY)
  set(CMAKE_FIND_ROOT_PATH "${C_COMPILER_DIR}/../avr")
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

  set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
  set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

  message(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
  message(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
  message(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")
endif()

include_directories(include)

add_subdirectory(src)

if(DEFINED AVR)
  add_subdirectory(examples)
endif()

enable_testing()
add_subdirectory(tests)