cmake_minimum_required(VERSION 3.19)

project(LearnVulkan CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(projectSetup)
setup_project_directories() 

# glfw configs
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glm)

add_subdirectory(common)
add_subdirectory(samples)