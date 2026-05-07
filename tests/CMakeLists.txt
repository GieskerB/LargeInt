project(LargeIntTests)

#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#
## Add GTest but exclude its internal targets from the "all" build
#add_subdirectory(googletest-1.17.0 EXCLUDE_FROM_ALL)

add_subdirectory(lib/googletest-1.17.0)
add_subdirectory(arithmetic_tests)
add_subdirectory(output_tests)