cmake_minimum_required(VERSION 3.29)
project(HTML_Validator)

set(CMAKE_CXX_STANDARD 20)

add_executable(HTML_Validator main.cpp
        HTMLChecker.h
        HTMLChecker.cpp)
