cmake_minimum_required(VERSION 3.30)

option(LODESTONE_APP_BUILD_JAVA_EXT "Build Lodestone.App.Java" ON)
option(LODESTONE_APP_BUILD_LCE_EXT "Build Lodestone.App.LCE" ON)

add_subdirectory(LodestoneCoreExt)

set(PLUGIN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

function(enable_plugin target)
#    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_DIR})
set_target_properties(${target} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_DIR}"
)
endfunction()

if (LODESTONE_APP_BUILD_JAVA_EXT)
    add_subdirectory(LodestoneJavaExt)

    add_dependencies(Lodestone.App Lodestone.App.Java)
endif()

if (LODESTONE_APP_BUILD_LCE_EXT)
    add_subdirectory(LodestoneLCEExt)

    add_dependencies(Lodestone.App Lodestone.App.LCE)
endif()

target_compile_definitions(Lodestone.App PRIVATE
        LODESTONE_APP_BUILD_JAVA_EXT
        LODESTONE_APP_BUILD_LCE_EXT
)

if (EMSCRIPTEN AND BUILD_SHARED_LIBS)
    target_link_options(Lodestone.App PRIVATE
        "SHELL:--preload-file ${PLUGIN_OUTPUT_DIR}"
    )
endif()