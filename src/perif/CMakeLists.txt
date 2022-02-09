add_avr_library(mod_perif STATIC
  ads1118.c
  sen0313.c
  ds18b20.c
)
avr_target_link_libraries(mod_perif mod_drivers mod_mcu)