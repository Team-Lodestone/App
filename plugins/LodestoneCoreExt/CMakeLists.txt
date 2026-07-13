cmake_minimum_required(VERSION 3.30)

add_library(Lodestone.App.Core INTERFACE)
target_sources(Lodestone.App.Core
        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
        include/LodestoneCoreExt/plugin/LodestoneAppExtension.h
)
target_include_directories(Lodestone.App.Core INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

setupLinter(Lodestone.App.Core)