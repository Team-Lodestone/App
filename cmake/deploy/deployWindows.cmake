include(${CMAKE_CURRENT_LIST_DIR}/deployCommon.cmake)

qt_generate_deploy_script(
        TARGET Lodestone.App
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
        CONTENT "
qt_deploy_runtime_dependencies(
    EXECUTABLE \"${executable_path}\"
    GENERATE_QT_CONF
    VERBOSE
)")

install(SCRIPT "${deploy_script}")