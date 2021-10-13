if(DEFINED AVR)
  add_subdirectory(mcu)
  add_subdirectory(drivers)
  add_subdirectory(perif)
endif(DEFINED AVR)

add_subdirectory(os)