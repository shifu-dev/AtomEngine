function (CreateTest TEST_NAME TEST_SOURCES)

    add_executable(${TEST_NAME} ${TEST_SOURCES})
    target_link_libraries(${TEST_NAME} AtomEngine)
    target_link_libraries(${TEST_NAME} Catch2WithMain)
    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 20)

    add_test(${TEST_NAME} ${TEST_NAME})

endfunction()

function (CreateTestFromSource TEST_SOURCE)

    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/AtomEngine/" "" TEST_NAME ${TEST_SOURCE})
    string(REPLACE "/Test" "-" TEST_NAME ${TEST_NAME})
    string(REPLACE "/" "-" TEST_NAME ${TEST_NAME})
    string(REPLACE ".cpp" "" TEST_NAME ${TEST_NAME})
    string(PREPEND TEST_NAME "Test-")

    CreateTest(${TEST_NAME} ${TEST_SOURCE})

endfunction()

file(GLOB_RECURSE TEST_SOURCES "*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    CreateTestFromSource(${TEST_SOURCE})
endforeach()