if(DEFINED AVR)
  add_subdirectory(mcu)
  add_subdirectory(drivers)
endif(DEFINED AVR)

add_subdirectory(os)