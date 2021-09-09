
add_executable(test_linked_queue test_linked_queue.c)
target_link_libraries(test_linked_queue unity mod_os)
add_test(${PROJECT_NAME} test_linked_queue)

add_executable(test_circulair_queue test_circulair_queue.c)
target_link_libraries(test_circulair_queue unity mod_os)
add_test(${PROJECT_NAME} test_circulair_queue)