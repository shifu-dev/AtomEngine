cmake_minimum_required(VERSION 3.0.0)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX)

# AtomEngine variables
set(ATOM_NAME "AtomEngine")
set(ATOM_DIR ${CMAKE_CURRENT_LIST_DIR})
set(ATOM_INCLUDE_DIR ${ATOM_DIR}/include)
set(ATOM_SOURCE_DIR ${ATOM_DIR}/src)
set(ATOM_TESTS_DIR ${ATOM_DIR}/tests)
set(ATOM_DOCS_DIR ${ATOM_DIR}/docs)
set(ATOM_BIN_DIR ${ATOM_DIR}/bin)
set(ATOM_OBJ_DIR ${ATOM_DIR}/bin-int)
set(ATOM_VENDOR_DIR ${ATOM_DIR}/vendor)
set(ATOM_LIB_TYPE "SHARED")

file(GLOB_RECURSE ATOM_SOURCES ${ATOM_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE ATOM_HEADERS ${ATOM_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE ATOM_HEADERS ${ATOM_INCLUDE_DIR}/*.hpp ${ATOM_HEADERS})

# AtomEngine library
add_library(${ATOM_NAME} ${ATOM_LIB_TYPE}
    ${ATOM_SOURCES} ${ATOM_HEADERS})

# AtomEngine properties
target_include_directories(${ATOM_NAME} PUBLIC ${ATOM_INCLUDE_DIR})
target_compile_definitions(${ATOM_NAME} PRIVATE ATOM_BUILD_DLL=1)
set_property(TARGET ${ATOM_NAME} PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET ${ATOM_NAME} PROPERTY CXX_STANDARD 17)