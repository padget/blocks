cmake_minimum_required (VERSION 2.6)
project (Blocks)
add_executable(Blocks ${CMAKE_SOURCE_DIR}/src/blocks.cpp)
set_property(TARGET Blocks PROPERTY CXX_STANDARD 17)

target_include_directories(Blocks PRIVATE ${CMAKE_SOURCE_DIR}/include)