cmake_minimum_required(VERSION 3.9)
project(bencode_lib)

set(SOURCES
    Parser.cpp
    Parser.hpp
    TokenType.hpp
    Token.hpp
    )
add_library(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)

if(BUILD_TESTING)
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
endif()
