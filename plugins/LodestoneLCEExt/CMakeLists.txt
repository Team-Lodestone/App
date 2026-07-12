cmake_minimum_required(VERSION 3.30)
project(Lodestone.App.LCE VERSION 1.0.2)

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    qt_add_plugin(Lodestone.App.LCE
            STATIC
            CLASS_NAME
            LodestoneLCEPlugin
    )
else()
    qt_add_plugin(Lodestone.App.LCE
            SHARED
            CLASS_NAME
            LodestoneLCEPlugin
    )
endif()
target_sources(Lodestone.App.LCE PRIVATE
        src/LodestoneLCEPlugin.cpp
)
target_sources(Lodestone.App.LCE PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        include/LodestoneLCEExt/LodestoneLCEPlugin.h
)
target_include_directories(Lodestone.App.LCE PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.App.LCE PUBLIC Lodestone.App.Core)
target_link_libraries(Lodestone.App.LCE PUBLIC
        Lodestone.Minecraft.Console

        Qt6::Core
)

enable_plugin(Lodestone.App.Java)

setupLinter(Lodestone.App.LCE)