include(FetchContent)

if (NOT TARGET Lodestone.Core)
    FetchContent_Declare(
            libLodestone
            GIT_REPOSITORY https://github.com/Team-Lodestone/libLodestone.git
            GIT_TAG main
            GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(libLodestone)
endif ()

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)
