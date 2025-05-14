# Lodestone App
The Lodestone app, which provides world and file editing.

For more information, check the official [Project Lodestone Website](https://team-lodestone.github.io)

## Building
Lodestone requires [Node.js](https://nodejs.org/), [Ninja](https://ninja-build.org/) (for [libLCE](https://github.com/DexrnZacAttack/libLCE)), and [CMake](https://cmake.org/download/) (for Emscripten SDK). A working C/C++ compiler is also required.

Additionally, [Lodestone-UI](https://github.com/Team-Lodestone/UI) must be cloned into the UI folder next to where Lodestone is.
```bash
git clone https://github.com/Team-Lodestone/UI
```

After installing prerequisites, the repo must be cloned recursively to include submodules.
```bash
git clone --recurse-submodules https://github.com/Team-Lodestone/App
cd App
npm install
```
This will clone and install all necessary dependencies.
To run the website, run the following command:
```bash
npm run dev
```
By default, Lodestone will be running on http://localhost:5173/App.

If you did not clone Lodestone with submodules, you can issue the following
command:
```bash
git submodule update --init --recursive
```

To recompile libLCE to WASM, issue the following command:
```bash
npm run liblce:compile
```