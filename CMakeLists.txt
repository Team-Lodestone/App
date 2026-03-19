cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.App VERSION 1.0.0)
set(PROJECT_VERSION_DEV 12) # used for dev versions, otherwise blank

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
file(GLOB_RECURSE FILES CONFIGURE_DEPENDS
        "include/*.h"
        "src/*.cpp"
        "rsrc/*.rc"
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Concurrent)
qt_standard_project_setup()

if (NOT TARGET Lodestone.Core)
    include(FetchContent)
    FetchContent_Declare(
            libLodestone
            GIT_REPOSITORY https://github.com/Team-Lodestone/libLodestone.git
            GIT_TAG main
            GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(libLodestone)
endif ()

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

qt_add_executable(Lodestone.App ${FILES})

if (WIN32)
    target_link_libraries(Lodestone.App PRIVATE "-lstdc++exp")
endif ()

target_include_directories(Lodestone.App
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
set_target_properties(Lodestone.App PROPERTIES
        OUTPUT_NAME "Lodestone"
)

target_link_libraries(Lodestone.App PUBLIC
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
        nbt++
        nlohmann_json
        bio-cpp20
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Concurrent
)

set(VERSIONS
        MAJOR
        MINOR
        PATCH
        DEV
)

foreach (k IN LISTS VERSIONS)
    if (DEFINED PROJECT_VERSION_${k})
        target_compile_definitions(Lodestone.App PUBLIC
                LODESTONE_APP_${k}_VERSION=${PROJECT_VERSION_${k}}
        )
    endif ()
endforeach ()

set(PRECOMPILED_EXTENSIONS
        Lodestone.Minecraft.Java
        Lodestone.Minecraft.Console
)

foreach (ext IN LISTS PRECOMPILED_EXTENSIONS)
    add_dependencies(Lodestone.App ${ext})

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/extensions)
    add_custom_command(TARGET Lodestone.App POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:${ext}>
            ${CMAKE_CURRENT_BINARY_DIR}/extensions
    )
endforeach ()

if (APPLE)
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
            LIBRARY DESTINATION Lodestone.App.app/Contents/Frameworks
            BUNDLE DESTINATION .
    )

    # we can't really add extensions into the binary I don't think
    # todo we should use qt's path garbage for this and provide a setting for it, then force it to use the appdata dir on macos
    #    foreach(ext IN LISTS PRECOMPILED_EXTENSIONS)
    #        install(TARGETS ${ext}
    #                LIBRARY DESTINATION Contents/Frameworks)
    #    endforeach ()

    set(executable_path "Lodestone.app")
else ()
    if (WIN32)
        set_target_properties(Lodestone.App PROPERTIES
                WIN32_EXECUTABLE TRUE
        )
    endif ()

    install(TARGETS Lodestone.App
            Lodestone.Level
            Lodestone.Conversion
            Lodestone.Core
            nbt++
            nlohmann_json
            bio-cpp20
            BUNDLE DESTINATION .
    )

    foreach (ext IN LISTS PRECOMPILED_EXTENSIONS)
        install(TARGETS ${ext}
                LIBRARY DESTINATION bin/extensions)
    endforeach ()

    set(executable_path "\${QT_DEPLOY_BIN_DIR}/$<TARGET_FILE_NAME:Lodestone.App>")
endif ()

if (APPLE OR WIN32)
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
endif ()

setupLinter(Lodestone.App)