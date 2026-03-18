cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.App VERSION 1.0.0)
set(PROJECT_VERSION_DEV 4) # used for dev versions, otherwise blank

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
endif()

qt_add_executable(Lodestone.App ${FILES})
target_include_directories(Lodestone.App
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.App PUBLIC
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
        nbt++
        bio
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

foreach(k IN LISTS VERSIONS)
    if (DEFINED PROJECT_VERSION_${k})
        target_compile_definitions(Lodestone.App PUBLIC
                LODESTONE_APP_${k}_VERSION=${PROJECT_VERSION_${k}}
        )
    endif()
endforeach ()

set(PRECOMPILED_EXTENSIONS
        Lodestone.Minecraft.Java
        Lodestone.Minecraft.Console
)

foreach(ext IN LISTS PRECOMPILED_EXTENSIONS)
    add_dependencies(Lodestone.App ${ext})

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/extensions)
    add_custom_command(TARGET Lodestone.App POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:${ext}>
            ${CMAKE_CURRENT_BINARY_DIR}/extensions
    )
endforeach ()

install(TARGETS Lodestone.App
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
        nbt++
        bio
        BUNDLE DESTINATION .
)

foreach(ext IN LISTS PRECOMPILED_EXTENSIONS)
    install(TARGETS ${ext}
    LIBRARY DESTINATION bin/extensions)
endforeach ()

set_target_properties(Lodestone.App PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
)

if(APPLE)
    set_target_properties(Lodestone.App PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "ProjectLodestone"
        MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.team-lodestone.LodestoneApp"
    )

    if (DEFINED PROJECT_VERSION_DEV)
        set_target_properties(Lodestone.App PROPERTIES
                MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
                MACOSX_BUNDLE_BUNDLE_VERSION_STRING ${PROJECT_VERSION}-dev.${PROJECT_VERSION_DEV}
        )
    else()
        set_target_properties(Lodestone.App PROPERTIES
                MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
                MACOSX_BUNDLE_BUNDLE_VERSION_STRING ${PROJECT_VERSION}
        )
    endif()
    
    set(executable_path "ProjectLodestone.app")
else()
    set(executable_path "\${QT_DEPLOY_BIN_DIR}/$<TARGET_FILE_NAME:Lodestone.App>")
endif()

if(APPLE OR WIN32)
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
endif()

setupLinter(Lodestone.App)