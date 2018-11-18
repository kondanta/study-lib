add_executable(
    unit_tests
    node_test.cpp
    list_test.cpp
    )

set_target_properties(
    unit_tests PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    )

target_link_libraries(
    unit_tests
    gtest_main
    singlylist
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
