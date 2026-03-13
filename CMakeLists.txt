cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.App VERSION 1.0.0)
set(PROJECT_VERSION_DEV 1) # used for dev versions, otherwise blank

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
file(GLOB_RECURSE FILES CONFIGURE_DEPENDS
        "include/*.h"
        "src/*.cpp"
        "rsrc/*.rc"
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Concurrent)
qt_standard_project_setup()


qt_add_executable(Lodestone.App ${FILES})
target_include_directories(Lodestone.App
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.App PRIVATE
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

setupLinter(Lodestone.App)