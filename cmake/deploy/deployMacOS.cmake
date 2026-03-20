install(TARGETS Lodestone.App
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
        nbt++
        nlohmann_json
        bio-cpp20
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION Lodestone.app/Contents/Frameworks
        BUNDLE DESTINATION .
)

set(executable_path "Lodestone.app")

qt_generate_deploy_script(
        TARGET Lodestone.App
        OUTPUT_SCRIPT deploy_script
        CONTENT "
    qt_deploy_runtime_dependencies(
        EXECUTABLE \"${executable_path}\"
        GENERATE_QT_CONF
        VERBOSE
    )")

install(SCRIPT "${deploy_script}")