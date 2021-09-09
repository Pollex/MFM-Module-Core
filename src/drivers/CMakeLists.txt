add_avr_library(mod_drivers STATIC
  ads1118.c
  sen0313.c
)
avr_target_link_libraries(mod_drivers mod_mcu)