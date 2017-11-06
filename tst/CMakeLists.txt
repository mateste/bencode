cmake_minimum_required(VERSION 3.9)
project(bencode_tst)
include(gtest/gtest.cmake)
include(CTest)

set(SOURCES
    Parser_test.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} bencode_lib gtest_main)
target_include_directories(${PROJECT_NAME} PRIVATE ../src)
add_test(NAME bencode_test COMMAND bencode_tst)
