cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.App VERSION 1.0.0)
set(PROJECT_VERSION_DEV 26) # used for dev versions, otherwise blank

set(CMAKE_CXX_STANDARD 23)

set(LODESTONE_UTILITIES_BUILD_TESTS OFF CACHE BOOL "Build Lodestone.Tests" FORCE)
set(BIO_TESTS OFF CACHE BOOL "Build libBIO tests" FORCE)

set(GLOB_PATHS
        "include/*.h"
        "src/*.cpp"
        "rsrc/*.rc"
        "rsrc/*.qrc"
)

if (WIN32)
    list(APPEND GLOB_PATHS
            "rsrc/windows/*.rc"
            "rsrc/windows/*.h"
            "${CMAKE_CURRENT_BINARY_DIR}/platform/windows/*.rc" #preprocessor
    )

    set(ICON "${CMAKE_CURRENT_SOURCE_DIR}/rsrc/assets/icons/icon.ico")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rsrc/windows/icon.rc.in
            ${CMAKE_CURRENT_BINARY_DIR}/platform/windows/icon.rc
            @ONLY
    )
endif ()

if(APPLE)
    list(APPEND GLOB_PATHS
        "rsrc/macos/*.icns"
    )
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
file(GLOB_RECURSE FILES CONFIGURE_DEPENDS ${GLOB_PATHS})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/fetchDeps.cmake)

if (EMSCRIPTEN)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Concurrent)
else()
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Concurrent DBus)
endif()
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(Lodestone.App ${FILES})

set_target_properties(Lodestone.App PROPERTIES ENABLE_EXPORTS TRUE)

if(EMSCRIPTEN)
    set_target_properties(Lodestone.App PROPERTIES
            QT_PLUGINS "platforms;imageformats"
    )

    if (BUILD_SHARED_LIBS)
        target_compile_options(Lodestone.App PRIVATE
                "-pthread"
        )

        target_link_options(Lodestone.App PRIVATE
                "-pthread"
                "-sPTHREAD_POOL_SIZE=4"
                "-sPTHREAD_POOL_DELAY_LOAD=1"

                "-sMAIN_MODULE=2"
                "-sEXPORT_ALL=1"
                "-sALLOW_TABLE_GROWTH=1"
                "-sSTRICT_JS=0"
                "-sDEFAULT_TO_CXX=1"
                "-sERROR_ON_UNDEFINED_SYMBOLS=0"

                "-sEXPORT_ES6=0"
                "-sMODULARIZE=0"

                "-sSHARED_MEMORY=1"
                "-sALLOW_MEMORY_GROWTH=1"
                "-sINITIAL_MEMORY=2147483648"

                "-Wl,--allow-multiple-definition"
                "-sWARN_ON_UNDEFINED_SYMBOLS=0"
                "-sERROR_ON_UNDEFINED_SYMBOLS=0"
                "-sNO_DISABLE_EXCEPTION_CATCHING"
        )
    endif()
endif()

target_include_directories(Lodestone.App
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(Lodestone.App PROPERTIES
        OUTPUT_NAME "Lodestone"
)

if (APPLE)
    set_target_properties(Lodestone.App PROPERTIES
            MACOSX_BUNDLE TRUE

            MACOSX_BUNDLE_ICON_FILE "Lodestone.icns"
            MACOSX_BUNDLE_BUNDLE_NAME "Project Lodestone"
            MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.team-lodestone.LodestoneApp"

            MACOSX_BUNDLE_COPYRIGHT "Team Lodestone, Dexrn ZacAttack"
    )

    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/rsrc/macos/Lodestone.icns PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")

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
endif()

if (WIN32)
    set(ICON "${CMAKE_CURRENT_SOURCE_DIR}/rsrc/assets/icons/icon.ico")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rsrc/windows/icon.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/icon.rc
        @ONLY
    )
    
    target_link_libraries(Lodestone.App PRIVATE "-lstdc++exp")
    set_target_properties(Lodestone.App PROPERTIES
            WIN32_EXECUTABLE TRUE
    )

    if (DEFINED PROJECT_VERSION_DEV)
        target_compile_definitions(Lodestone.App PRIVATE
                LODESTONE_APP_VERSION="\\"${PROJECT_VERSION}-dev.${PROJECT_VERSION_DEV}\\""
        )
    else ()
        target_compile_definitions(Lodestone.App PRIVATE
                LODESTONE_APP_VERSION="\\"${PROJECT_VERSION}\\""
        )
    endif ()

    target_compile_definitions(Lodestone.App PRIVATE
            LODESTONE_APP_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
    )
endif ()

target_compile_definitions(Lodestone.App PRIVATE
        $<$<BOOL:${BUILD_SHARED_LIBS}>:BUILD_SHARED_LIBS>
)

target_link_libraries(Lodestone.App PUBLIC
        Lodestone.App.Core
        Lodestone.Level
        Lodestone.Common
        Lodestone.Core
        Lodestone.Conversion
        nbt++
        nlohmann_json
        bio-cpp20

        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Concurrent
)
target_link_options(Lodestone.App PRIVATE
        "-L${CMAKE_BINARY_DIR}/libLodestone/projects/Libraries/Common"
        "-L${CMAKE_BINARY_DIR}/libLodestone/projects/Libraries/Level"
)
if (NOT EMSCRIPTEN)
    target_link_libraries(Lodestone.App PUBLIC
        Qt6::DBus # macos implodes without this
    )
endif()

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

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/precompile.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/deploy/deploy.cmake)

add_subdirectory(plugins)

if(EMSCRIPTEN)
    target_link_options(Lodestone.App PRIVATE
            -gsource-map
    )
    if (NOT BUILD_SHARED_LIBS)
        if (LODESTONE_APP_BUILD_JAVA_EXT)
            #        target_link_libraries(Lodestone.App PRIVATE
            #                "-Wl,--whole-archive"
            #                Lodestone.App.Java
            #                "-Wl,--no-whole-archive"
            #        )
            target_link_libraries(Lodestone.App PRIVATE
                    Lodestone.App.Java
            )
        endif ()

        if (LODESTONE_APP_BUILD_LCE_EXT)
            #        target_link_libraries(Lodestone.App PRIVATE
            #                "-Wl,--whole-archive"
            #                Lodestone.App.LCE
            #                "-Wl,--no-whole-archive"
            #        )
            target_link_libraries(Lodestone.App PRIVATE
                    Lodestone.App.LCE
            )
        endif ()
    endif ()
else()
    # Link against extensions dynamically
    if(LODESTONE_APP_BUILD_JAVA_EXT)
        target_link_libraries(Lodestone.App PRIVATE
                Lodestone.Minecraft.Java
        )
    endif()

    if(LODESTONE_APP_BUILD_LCE_EXT)
        target_link_libraries(Lodestone.App PRIVATE
                Lodestone.Minecraft.Console
        )
    endif()
endif()

if(EMSCRIPTEN)
    qt_generate_deploy_app_script(
        TARGET Lodestone.App
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
endif()

setupLinter(Lodestone.App)