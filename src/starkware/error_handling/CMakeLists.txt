add_library(error_handling error_handling.cc)
target_link_libraries(error_handling third_party dw)

add_executable(error_handling_test error_handling_test.cc)
target_link_libraries(error_handling_test error_handling starkware_gtest)
add_test(error_handling_test error_handling_test)
