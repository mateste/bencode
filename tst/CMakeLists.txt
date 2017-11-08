cmake_minimum_required(VERSION 3.9)
project(bencode_tst)
include(gtest/gtest.cmake)
include(CTest)

set(SOURCES
    Parser_test.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(${PROJECT_NAME} PRIVATE bencode gtest_main)
target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
add_test(NAME bencode_test COMMAND bencode_tst)
