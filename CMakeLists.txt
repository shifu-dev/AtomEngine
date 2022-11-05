cmake_minimum_required(VERSION 3.0.0)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX)

set(AtomEngine_DIR ${CMAKE_CURRENT_SOURCE_DIR})
find_package(AtomEngine CONFIG REQUIRED)

enable_testing()
add_subdirectory(tests)