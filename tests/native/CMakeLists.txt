add_executable(test_linked_queue test_linked_queue.c)
target_link_libraries(test_linked_queue unity mod_os)
add_test(NAME test_linked_queue COMMAND test_linked_queue)

add_executable(test_circulair_queue test_circulair_queue.c)
target_link_libraries(test_circulair_queue unity mod_os)
add_test(NAME test_circulair_queue COMMAND test_circulair_queue)

add_executable(test_os_lock test_os_lock.c)
target_link_libraries(test_os_lock unity mod_os)
add_test(NAME test_os_lock COMMAND test_os_lock)