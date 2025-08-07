add_executable(HelloTriangle main.cpp utils.h)

target_link_libraries(HelloTriangle PRIVATE common)

# 如果需要着色器，就加上
copy_resources_to_target(HelloTriangle)