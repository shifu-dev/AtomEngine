cmake_minimum_required(VERSION 3.0.0)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX)

set(ATOM_ENGINE_LIB "AtomEngine")
set(ATOM_ENGINE_LIB_TYPE "SHARED")

file(GLOB_RECURSE ATOM_ENGINE_SOURCES ${ATOM_ENGINE_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE ATOM_ENGINE_HEADERS ${ATOM_ENGINE_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE ATOM_ENGINE_HEADERS ${ATOM_ENGINE_INCLUDE_DIR}/*.hpp ${ATOM_ENGINE_HEADERS})

######################################################################
# AtomEngine library

add_library(
    ${ATOM_ENGINE_LIB} ${ATOM_ENGINE_LIB_TYPE}
    ${ATOM_ENGINE_SOURCES}
    ${ATOM_ENGINE_HEADERS}
)

target_include_directories(${ATOM_ENGINE_LIB} PUBLIC ${ATOM_ENGINE_INCLUDE_DIR})
target_include_directories(${ATOM_ENGINE_LIB} PRIVATE ${ATOM_ENGINE_SOURCE_DIR})
target_compile_definitions(${ATOM_ENGINE_LIB} PRIVATE ATOM_BUILD_DLL=1)
set_property(TARGET ${ATOM_ENGINE_LIB} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${ATOM_ENGINE_LIB} PROPERTY CXX_STANDARD 17)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    target_compile_options(${ATOM_ENGINE_LIB} PUBLIC "/permissive-")
endif()