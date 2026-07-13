cmake_minimum_required(VERSION 3.30)

option(LODESTONE_APP_BUILD_JAVA_EXT "Build Lodestone.App.Java" ON)
option(LODESTONE_APP_BUILD_LCE_EXT "Build Lodestone.App.LCE" ON)

add_subdirectory(LodestoneCoreExt)

# TODO: Refactor this to be programmatically
set(PLUGIN_DIR ../../plugins)

function(enable_plugin target)
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_DIR})
endfunction()

if (LODESTONE_APP_BUILD_JAVA_EXT)
    add_subdirectory(LodestoneJavaExt)
endif()

if (LODESTONE_APP_BUILD_LCE_EXT)
    add_subdirectory(LodestoneLCEExt)
endif()

target_compile_definitions(Lodestone.App PRIVATE
        LODESTONE_APP_BUILD_JAVA_EXT
        LODESTONE_APP_BUILD_LCE_EXT
)