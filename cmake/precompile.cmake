set(PRECOMPILED_EXTENSIONS
        Lodestone.Minecraft.Java
        Lodestone.Minecraft.Console
)

set(EXTENSIONS_DIR "${CMAKE_CURRENT_BINARY_DIR}/extensions")

foreach (ext IN LISTS PRECOMPILED_EXTENSIONS)
    add_dependencies(Lodestone.App ${ext})

    file(MAKE_DIRECTORY ${EXTENSIONS_DIR})
    add_custom_command(TARGET Lodestone.App POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:${ext}>
            ${EXTENSIONS_DIR}
    )
endforeach ()

if(EMSCRIPTEN AND BUILD_SHARED_LIBS)
    target_link_options(Lodestone.App PRIVATE
            "SHELL:--preload-file \"${EXTENSIONS_DIR}@/extensions\""
    )
endif()