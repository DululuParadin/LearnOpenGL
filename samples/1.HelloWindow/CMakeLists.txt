add_executable(HelloWindow main.cpp)

target_link_libraries(HelloWindow PRIVATE common)

# 如果需要着色器，就加上
copy_resources_to_target(HelloWindow)