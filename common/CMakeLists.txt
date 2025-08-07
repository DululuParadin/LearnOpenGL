set(GLAD_SRC_DIR ${CMAKE_SOURCE_DIR}/third_party/glad/src)
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third_party/glad/include)

file(GLOB_RECURSE COMMON_SOURCES "src/*.cpp" "src/*.h" "api/*.h")

add_library(common STATIC
	${GLAD_SRC_DIR}/glad.c
	${COMMON_SOURCES}
)

target_include_directories(common
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/api
		${CMAKE_CURRENT_SOURCE_DIR}/api/utils
        ${GLAD_INCLUDE_DIR}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/src/utils
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