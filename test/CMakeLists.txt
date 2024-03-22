add_executable(my_test test.cpp)

add_custom_target(start_test COMMAND my_test)

target_link_libraries(my_test PRIVATE gtest_main stack)

add_executable(main main.cpp)

add_custom_target(parse_file COMMAND main)

target_link_libraries(main PRIVATE stack parser)

target_include_directories(my_test PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
)
target_include_directories(main PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
)
