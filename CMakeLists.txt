cmake_minimum_required(VERSION 3.15)
project(avrodemo CXX)

add_library(avrodemo src/avrodemo.cpp)
target_include_directories(avrodemo PUBLIC include)

set_target_properties(avrodemo PROPERTIES PUBLIC_HEADER "include/avrodemo.h")
install(TARGETS avrodemo)
