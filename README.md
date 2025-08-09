# Learn Vulkan
## Project Goals
- Modern Practices: Utilizes best practices for modern C++ (C++23) and CMake (3.15+), with a focus on safe, clear, and idiomatic code.
- Modular Learning: Each sample is a self-contained, compilable sub-project demonstrating a specific Vulkan or graphics concept, such as instance creation, swapchain setup, synchronization, descriptor sets, etc.
- Clarity and Simplicity: Prioritizes readable, didactic code that reveals Vulkan's API principles, while avoiding unnecessary abstraction in early samples.
- Cross-Platform Build: Designed for cross-platform development using CMake, with initial focus and testing on Windows.

This project, based on [VulkanTutorial](https://vulkan-tutorial.com/) and [EasyVulkan](https://easyvulkan.github.io/), is to practice the Vulkan API and learn about computer graphics.

## Features
Automatic Sample Discovery: The root `samples/CMakeLists.txt` automatically finds and adds all subdirectories as executable targets. Adding a new sample requires no parent build script changes.
Dependency Management: Uses Git submodules for third-party dependencies (like GLFW, glm ...), ensuring reproducible builds with no manual setup.
Shared Code Library: The common directory provides reusable utilities across samples, such as Vulkan initialization helpers, resource managers, math types, and camera controls.
## Prerequisites (Windows)
Before building this project, please install:
1. Visual Studio 2019 or newer:

- Make sure the "Desktop development with C++" workload is installed.
- Download: visualstudio.microsoft.com
2. CMake (3.15 or newer):

- During installation, check "Add CMake to the system PATH".
- Download: cmake.org/download

3. Vulkan SDK:

- Required for headers, validation layers, and runtime.
- Download: lunarg.com/vulkan-sdk

1. Git:

- Required to clone this repository and submodules.
- Download: git-scm.com

## Building on Windows
```bash
git clone https://github.com/DululuParadin/LearnOpenGL.git
cd LearnOpenGL
git checkout vulkan
git submodule update --init --recursive
mkdir build
cd build
cmake ..
```
After Building
All generated project files (e.g., `.sln`, `.vcxproj`) are located in the build directory. Open the `.sln` file in Visual Studio for coding, building, and debugging.

## Project Structure
```txt
.
├── assets/
│   ├── shaders/
│   ├── models/
│   └── textures/
├── cmake/
│   └── (custom modules, e.g., projectSetup.cmake)
├── common/
│   └── (shared Vulkan helpers and utilities)
├── samples/
│   ├── HelloVulkan/
│   │   ├── main.cpp
│   │   └── CMakeLists.txt
│   └── ... (additional samples)
├── third_party/
│   └── (libraries: glfw, glm, volk, VMA, etc.)
│
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## Getting Started
Each sample is designed to build and run independently. Start with HelloVulkan to see a minimal Vulkan window. Move to more advanced samples to explore swapchain management, uniform buffers, descriptor sets, pipelines, and more.