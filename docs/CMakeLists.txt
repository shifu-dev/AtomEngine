find_package(Doxygen REQUIRED)

set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
file(GLOB_RECURSE DOXYGEN_INPUT_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)

string(REPLACE ";" "\" \\\n\"" DOXYGEN_INPUT "${DOXYGEN_INPUT_FILES}")

set(DOXYGEN_CONFIG_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
set(DOXYGEN_CONFIG ${DOXYGEN_CURRENT_BINARY_DIR}doxygen.conf)
set(DOXYGEN_STAMP ${DOXYGEN_CURRENT_BINARY_DIR}doxygen.stamp)

set(DOXYGEN_HTML_EXTRA_STYLESHEETS ${CMAKE_SOURCE_DIR}/vendors/doxygen-awesome-css/doxygen-awesome.css)
set(DOXYGEN_HTML_LAYOUT ${CMAKE_CURRENT_LIST_DIR}/doxygen-layout.xml)

configure_file(${DOXYGEN_CONFIG_IN} ${DOXYGEN_CONFIG})

######################################################################
# CleanDocs

add_custom_target(CleanDocs)

add_custom_command(
    TARGET CleanDocs
    VERBATIM

    COMMAND ${CMAKE_COMMAND} -E echo  "Cleaning Docs..."
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${DOXYGEN_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${DOXYGEN_CONFIG}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${DOXYGEN_STAMP}
)

######################################################################
# BuildDocs

add_custom_command(
    VERBATIM

    OUTPUT ${DOXYGEN_STAMP}
    DEPENDS ${DOXYGEN_INPUT_FILES}
    DEPENDS ${DOXYGEN_CONFIG_IN}
    DEPENDS ${DOXYGEN_HTML_LAYOUT}
    DEPENDS ${DOXYGEN_HTML_EXTRA_STYLESHEETS}

    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning Docs..."
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${DOXYGEN_OUTPUT}

    COMMAND ${CMAKE_COMMAND} -E echo "Generating Docs..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
    COMMAND ${CMAKE_COMMAND} -E touch ${DOXYGEN_STAMP}
)

add_custom_target(BuildDocs ALL
    DEPENDS ${DOXYGEN_STAMP}
)

add_custom_target(BuildDocsForce
    VERBATIM

    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning Docs..."
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${DOXYGEN_OUTPUT}

    COMMAND ${CMAKE_COMMAND} -E echo "Generating Docs..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
)
