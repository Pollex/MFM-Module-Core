set(MOD_OS_FILES
  circulair_queue.c
  linked_queue.c
  os.c
)

if(DEFINED AVR)
  add_avr_library(mod_os STATIC ${MOD_OS_FILES})
else()
  add_library(mod_os STATIC ${MOD_OS_FILES})
endif()