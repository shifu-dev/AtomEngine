include(FetchContent)
include(CTest)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

file (GLOB_RECURSE TEST_SOURCES "*.cpp")
set (TEST_NAME "Tests")
add_executable(${TEST_NAME} ${TEST_SOURCES})
target_link_libraries(${TEST_NAME} Catch2::Catch2WithMain)
add_test(${TEST_NAME} ${TEST_NAME})