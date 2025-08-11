#include "hello_triangle.h"

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        LGL_LOGE("%s", e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}