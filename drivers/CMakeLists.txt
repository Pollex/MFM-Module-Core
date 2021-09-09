file(GLOB SRC_FILES "*.c") # Load all files in src folder

if(DEFINED AVR)
  add_avr_library(drivers ${SRC_FILES})
else()
  add_library(drivers ${SRC_FILES})
endif(DEFINED AVR)