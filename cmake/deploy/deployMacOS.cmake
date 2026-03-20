set_target_properties(Lodestone.App PROPERTIES
        MACOSX_BUNDLE TRUE

        MACOSX_BUNDLE_BUNDLE_NAME "Project Lodestone"
        MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.team-lodestone.LodestoneApp"

        MACOSX_BUNDLE_COPYRIGHT "Team Lodestone, Dexrn ZacAttack"
)

if (DEFINED PROJECT_VERSION_DEV)
    set_target_properties(Lodestone.App PROPERTIES
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_BUNDLE_VERSION_STRING ${PROJECT_VERSION}-dev.${PROJECT_VERSION_DEV}
    )
else ()
    set_target_properties(Lodestone.App PROPERTIES
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_BUNDLE_VERSION_STRING ${PROJECT_VERSION}
    )
endif ()

install(TARGETS Lodestone.App
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
        nbt++
        nlohmann_json
        bio-cpp20
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION Lodestone.App.app/Contents/Frameworks
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