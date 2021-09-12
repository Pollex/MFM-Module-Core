

if(DEFINED AVR)
  add_avr_library(unity STATIC Unity/src/unity.c)
  avr_target_include_directories(unity PUBLIC Unity/src)
  add_subdirectory(avr)
else()
  add_library(unity STATIC Unity/src/unity.c)
  target_include_directories(unity PUBLIC Unity/src)
  add_subdirectory(native)
endif()