include(${CMAKE_CURRENT_LIST_DIR}/deployCommon.cmake)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/rsrc/assets/icons/icon.svg DESTINATION share/icons/hicolor/scalable/apps
RENAME "Lodestone.svg")

include(CPack)

set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_PACKAGE_NAME "Project Lodestone")