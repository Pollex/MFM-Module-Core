include(CTest)
add_library(unity STATIC Unity/src/unity.c)
target_include_directories(unity PUBLIC Unity/src)

if(DEFINED AVR)
  add_subdirectory(avr)
else()
  add_subdirectory(native)
endif(DEFINED AVR)