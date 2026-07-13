cmake_minimum_required(VERSION 3.30)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(CMAKE_AUTOMOC ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    qt_add_plugin(Lodestone.App.Java
            STATIC
            CLASS_NAME
            LodestoneJavaPlugin
    )
else()
    qt_add_plugin(Lodestone.App.Java
            SHARED
            CLASS_NAME
            LodestoneJavaPlugin
    )
endif()
target_sources(Lodestone.App.Java PRIVATE
        src/LodestoneJavaPlugin.cpp
)
target_sources(Lodestone.App.Java PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
        include/LodestoneJavaExt/LodestoneJavaPlugin.h
)
target_include_directories(Lodestone.App.Java PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.App.Java PUBLIC Lodestone.App.Core)
target_link_libraries(Lodestone.App.Java PUBLIC
        Lodestone.Minecraft.Java

        Qt6::Core
)

enable_plugin(Lodestone.App.Java)

setupLinter(Lodestone.App.Java)