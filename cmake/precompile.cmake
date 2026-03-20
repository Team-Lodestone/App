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