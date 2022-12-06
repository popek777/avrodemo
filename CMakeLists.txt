cmake_minimum_required(VERSION 3.15)
project(avrodemo CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(avrodemo
  avrodemo.cpp
  generic_type_usecase.cpp)

target_link_libraries(avrodemo ${CONAN_LIBS})
