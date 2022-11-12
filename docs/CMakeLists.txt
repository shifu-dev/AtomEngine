find_package(Doxygen REQUIRED)

set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen)

file(GLOB_RECURSE DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/include/*.hpp)
string(REPLACE ";" "\" \\\n\"" DOXYGEN_INPUT "${DOXYGEN_INPUT}")

set(DOXYGEN_CONFIG_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
set(DOXYGEN_CONFIG ${DOXYGEN_OUTPUT}/doxygen.conf)
set(DOXYGEN_STAMP ${DOXYGEN_OUTPUT}/doxygen.stamp)

configure_file(${DOXYGEN_CONFIG_IN} ${DOXYGEN_CONFIG})

######################################################################
# CleanDocs

add_custom_target(CleanDocs)

add_custom_command(
    TARGET CleanDocs
    VERBATIM

    COMMENT "Cleaning Docs..."
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${DOXYGEN_OUTPUT}/html
)

######################################################################
# BuildDocs

add_custom_command(
    OUTPUT ${DOXYGEN_STAMP}
    VERBATIM

    COMMENT "Generating Docs..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
    COMMAND ${CMAKE_COMMAND} -E touch ${DOXYGEN_STAMP}
)

add_custom_target(BuildDocs ALL
    DEPENDS CleanDocs
    DEPENDS ${DOXYGEN_STAMP}
)