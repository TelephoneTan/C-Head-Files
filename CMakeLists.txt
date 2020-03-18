cmake_minimum_required (VERSION 3.16.5)

project ("C++ Headers")

add_executable (CPP_HEADERS "example.cpp")

include_directories(.)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "/source-charset:utf-8 /execution-charset:utf-8 /validate-charset /std:c++17")
