cmake_minimum_required(VERSION 3.0.0)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE ATOM_ENGINE_SOURCES ${ATOM_ENGINE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE ATOM_ENGINE_HEADERS ${ATOM_ENGINE_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE ATOM_ENGINE_HEADERS ${ATOM_ENGINE_INCLUDE_DIR}/*.hpp ${ATOM_ENGINE_HEADERS})

######################################################################
# AtomEngine library

add_library(AtomEngine SHARED
    ${ATOM_ENGINE_SOURCES}
    ${ATOM_ENGINE_HEADERS}
)

target_include_directories(AtomEngine PUBLIC ${ATOM_ENGINE_INCLUDE_DIR})
target_include_directories(AtomEngine PRIVATE ${ATOM_ENGINE_SOURCE_DIR})
target_compile_definitions(AtomEngine PRIVATE ATOM_BUILD_DLL=1)
set_property(TARGET AtomEngine PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET AtomEngine PROPERTY CXX_STANDARD 17)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    target_compile_options(AtomEngine PUBLIC "/permissive-")
endif()