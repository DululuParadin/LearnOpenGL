file(GLOB_RECURSE COMMON_SOURCES "src/*.cpp" "src/*.h" "api/*.h")

add_library(common STATIC
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

find_package(Vulkan REQUIRED)

target_link_libraries(common 
    PUBLIC glfw glm Vulkan::Vulkan
)