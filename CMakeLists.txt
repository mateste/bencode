cmake_minimum_required(VERSION 3.9)
project(bencode)

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tst)
endif()
