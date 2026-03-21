include(${CMAKE_CURRENT_LIST_DIR}/deployCommon.cmake)

qt_generate_deploy_app_script(
        TARGET Lodestone.App
        OUTPUT_SCRIPT deploy_script
)

install(SCRIPT "${deploy_script}")