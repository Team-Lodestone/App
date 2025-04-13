#!/bin/bash

# region Logger
RUNNING="[$(basename "$0")]"

# region Colors
CYAN='\e[36m'
YELLOW='\e[33m'
RED='\e[31m'
GREEN='\e[32m'
RESET='\e[0m'
# endregion

# region Functions

error() {
    echo -e "${CYAN}${RUNNING}${RESET} ${YELLOW}Error: ${RED}$1${RESET}"
    exit 1
}

msg() {
    echo -e "${CYAN}${RUNNING}${RESET} ${GREEN}$1${RESET}"
}

# endregion 

# endregion

# region Check for dependencies

clear

msg "Checking dependencies"
# Make sure libLCE is cloned properly
if [ ! -e "./deps/libLCE/external/emsdk/emsdk" ]; then
    error "Failed to find emsdk, was libLCE cloned correctly? Make sure you cloned the Lodestone App recursively."
fi

# check if Ninja exists
if ! command -v ninja > /dev/null; then
    error "Ninja is not installed! Please install Ninja."
fi

# whyyyyyyyyyyyyyyyyyyy
if ! command -v dos2unix > /dev/null; then
    error "dos2unix is not installed! Either manually convert the line endings of emsdk or install dos2unix."
fi

# endregion

# region Emscripten

msg "Setting up Emscripten shell scripts"

# execute bit
chmod +rx ./deps/libLCE/external/emsdk/emsdk_env.sh
chmod +x ./deps/libLCE/external/emsdk/emsdk

# annoying
dos2unix ./deps/libLCE/external/emsdk/emsdk
dos2unix ./deps/libLCE/external/emsdk/emsdk_env.sh

# Set up Emscripten
msg "Setting up Emscripten"
./deps/libLCE/external/emsdk/emsdk install latest
if [ $? -ne 0 ]; then
    error "Failed to install Emscripten"
fi

./deps/libLCE/external/emsdk/emsdk activate latest
if [ $? -ne 0 ]; then
    error "Failed to activate Emscripten"
fi

msg "Setting up Emscripten ENV"
source "$(realpath "./deps/libLCE/external/emsdk/emsdk_env.sh")"

# endregion

# region CMake

# region Configure CMake

em_folder_path=$(realpath "deps/libLCE/external/emsdk/upstream/emscripten")

if [ -f "deps/libLCE/em-build/CMakeCache.txt" ]; then
    msg "Deleting leftover CMakeCache"
    rm -rf "deps/libLCE/em-build/CMakeCache.txt"
fi

if [ -d "deps/libLCE/em-build/CMakeFiles" ]; then
    msg "Deleting leftover CMakeFiles directory"
    rm -rf "deps/libLCE/em-build/CMakeFiles"
fi

msg "Setting up CMake"
cmake -G "Ninja" \
  -B "deps/libLCE/em-build" \
  -S "deps/libLCE" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXE_LINKER_FLAGS="--bind" \
  -DEMSCRIPTEN_DIR="$em_folder_path" \
  -DCMAKE_TOOLCHAIN_FILE="$(realpath "$em_folder_path/cmake/Modules/Platform/Emscripten.cmake")"

if [ $? -ne 0 ]; then
    error "Failed to set up CMake"
fi

# endregion

# region Compile
msg "Compiling libLCE"
cmake --build deps/libLCE/em-build --config Release --target libLCE
if [ $? -ne 0 ]; then
    error "Build failed!"
fi

# endregion

# endregion

# region Finish up

# Copy built WASM files
msg "Copying build files to wasm folder"
cp deps/libLCE/em-build/*.wasm src/wasm
cp deps/libLCE/em-build/*.js src/wasm

if [ $? -ne 0 ]; then
    error "Failed to copy build files"
fi

msg "Done!"
exit 0

# endregion
