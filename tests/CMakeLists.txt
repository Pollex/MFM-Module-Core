add_library(unity STATIC Unity/src/unity.c)
target_include_directories(unity PUBLIC Unity/src)

add_executable(test_linked_queue test_linked_queue.c)
target_link_libraries(test_linked_queue unity)
add_test(${PROJECT_NAME} test_linked_queue)