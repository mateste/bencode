cmake_minimum_required(VERSION 3.9)
project(bencode)

set(SOURCES
    src/Parser.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Weverything -Wno-c++98-compat -Wno-padded)
endif()

if(BUILD_TESTING)
    target_compile_options(${PROJECT_NAME} PUBLIC --coverage)
    add_subdirectory(tst)
endif()
