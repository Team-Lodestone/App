@echo off
cls

rem Make sure libLCE is cloned properly
IF NOT EXIST deps\libLCE\external\emsdk\emsdk.bat (
set lodestone_liblce_error=Failed to find emsdk.bat, was libLCE cloned correctly? Make sure you cloned the Lodestone App recursively.
goto error
)

where ninja >nul 2>&1
if errorlevel 1 (
    set lodestone_liblce_error=Ninja is NOT on PATH. Please install it/add it to your PATH if already installed.
    goto error
)

rem Set up Emscripten
echo Setting up Emscripten
call deps\libLCE\external\emsdk\emsdk install latest
if errorlevel 1 (
    set lodestone_liblce_error=Failed to install Emscripten
    goto error
)

call deps\libLCE\external\emsdk\emsdk activate latest
if errorlevel 1 (
    set lodestone_liblce_error=Failed to activate Emscripten
    goto error
)

rem Configure CMake
echo Setting up CMake
for %%I in ("deps/libLCE/external/emsdk/upstream/emscripten") do set em_folder_path=%%~fI
for %%I in ("%em_folder_path%/cmake/Modules/Platform/Emscripten.cmake") do set em_cmake_path=%%~fI

IF EXIST deps\libLCE\em-build\CMakeCache.txt ( del deps\libLCE\em-build\CMakeCache.txt /s /q )
IF EXIST deps\libLCE\em-build\CMakeFiles ( rd deps\libLCE\em-build\CMakeFiles /s /q )

cmake -G "Ninja" -B deps\libLCE\em-build -S deps\libLCE -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="--bind" -DEMSCRIPTEN_DIR="%em_folder_path%" -DCMAKE_TOOLCHAIN_FILE="%em_cmake_path%"
if errorlevel 1 (
    set lodestone_liblce_error=Failed to set up CMake
    goto error
)


rem Build
echo Building libLCE
cmake --build deps\libLCE\em-build --config Release --target libLCE
if errorlevel 1 (
    set lodestone_liblce_error=Build failed
    goto error
)


rem Copy built WASM files
echo Copying build files to wasm folder
xcopy deps\libLCE\em-build\*.wasm src\wasm /Y
xcopy deps\libLCE\em-build\*.js src\wasm /Y
if errorlevel 1 (
    set lodestone_liblce_error=Failed to copy build files
    goto error
)

echo Done!
goto exit

:error
rem long name cuz need to not conflict
echo Error: %lodestone_liblce_error%
:exit