# Learn OpenGL

## Project Goals
Modern Practices: Utilizes best practices for modern C++ (C++17/20) and modern CMake (3.15+).
Modular Learning: Each sample is an independent, compilable sub-project focusing on a specific graphics concept, such as window creation, rendering a triangle, texture mapping, etc.
Clarity and Simplicity: The code prioritizes clarity and avoids premature abstraction to better illustrate the underlying API principles.
Cross-Platform Build: Designed for cross-platform support using CMake, currently developed and tested primarily on Windows.

This project, based on [LearnOpenGL](https://learnopengl.com/), is to practice the OpenGL API and learn about computer graphics.

## Features
Automatic Sample Discovery: The root `samples/CMakeLists.txt` automatically discovers and adds all subdirectories as executable targets. Adding a new sample requires no modification to parent build scripts.
Dependency Management: Uses Git submodule to automatically download and build third-party dependencies (like GLFW and GLM), eliminating the need for manual setup.
Shared Code Library: The common directory provides shared utilities across samples, such as camera controls, model loading, etc.


## Prerequisites (Windows)
Before compiling this project, ensure you have the following software installed:

1. Visual Studio 2019 or newer:
  - Ensure the "Desktop development with C++" workload is installed.
  - Download at: visualstudio.microsoft.com

2. CMake (3.15 or newer):
  - During installation, be sure to check "Add CMake to the system PATH for all users" or "for current user".
  - Download at: cmake.org/download

3. Git:
  - Required to clone this repository.
  - Download at: git-scm.com

## Building on Windows
```bash
git clone https://github.com/DululuParadin/LearnOpenGL.git
cd LearnOpenGL
git submodule update --init --recursive
mkdir build
cd build
cmake ..
```

### After Building
All generated project files (e.g., `.sln`, `.vcxproj`) are located in the build directory. You can open the `.sln` file with Visual Studio at any time to code and debug.

## Project Structure
```txt
.
├── assets/
│   ├── models/
│   ├── shaders/
│   └── textures/
├── cmake/
│   └── (custom modules, e.g., projectSetup.cmake)
├── common/
│   └── (base files)
├── samples/
│   ├── HelloOpenGL/
│   │   ├── main.cpp
│   │   └── CMakeLists.txt
│   └── ... (more samples)
├── third_party/
│   └── (libraries like glfw, glm, etc.)
│
├── .gitignore
├── CMakeLists.txt
└── README.md
```
