install(TARGETS Lodestone.App
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
        nbt++
        nlohmann_json
        bio-cpp20
        BUNDLE DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

foreach (ext IN LISTS PRECOMPILED_EXTENSIONS)
    install(TARGETS ${ext}
            LIBRARY DESTINATION bin/extensions)
endforeach ()

set(executable_path "\${QT_DEPLOY_BIN_DIR}/$<TARGET_FILE_NAME:Lodestone.App>")