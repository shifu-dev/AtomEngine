cmake_minimum_required(VERSION 3.0.0)
project(AtomEngineSandbox VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SANDBOX_SOURCES *.cpp)
file(GLOB_RECURSE SANDBOX_HEADERS *.hpp)

if (SANDBOX_SOURCES)
    add_executable(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})

    target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_LIST_DIR})
    target_link_libraries(Sandbox PRIVATE AtomEngine)
endif()