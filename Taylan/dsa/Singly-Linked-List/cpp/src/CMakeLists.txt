add_library(singlylist "")

#TODO
# configure_file(
#     "${PROJECT_SOURCE_DIR}/cmake/config.h.in"
#     "${PROJECT_BINARY_DIR}/config.h"
#     )

target_sources(
    singlylist
    PRIVATE
    node.cpp
    list.cpp
      ${PROJECT_SOURCE_DIR}/include/node.hpp
      ${PROJECT_SOURCE_DIR}/include/list.hpp
    )

target_include_directories(
    singlylist
    PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/include
      $<INSTALL_INTERFACE:include>
    )

install(TARGETS singlylist
    EXPORT SinglyTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES
    ${PROJECT_SOURCE_DIR}/include/node.hpp
    ${PROJECT_SOURCE_DIR}/include/list.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/SinglyConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)
install(
    EXPORT SinglyTargets
    NAMESPACE SinglyList::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Singly"
)
install(
    FILES
      "${PROJECT_SOURCE_DIR}/cmake/SinglyConfig.cmake"
      "${PROJECT_BINARY_DIR}/SinglyConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Singly"
)
