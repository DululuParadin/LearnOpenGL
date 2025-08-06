set(GLAD_SRC_DIR ${CMAKE_SOURCE_DIR}/third_party/glad/src)
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third_party/glad/include)

add_library(common STATIC
    ${GLAD_SRC_DIR}/glad.c
)

target_include_directories(common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLAD_INCLUDE_DIR}
)

target_link_libraries(common 
    PUBLIC glfw glm
)

if(MSVC)
    target_link_libraries(common PRIVATE opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(common PRIVATE OpenGL::GL)
endif()