#include <vector>
#include <vulkan/vulkan.h>
#include "mlog.h"

int main()
{
    VkApplicationInfo appInfo{
        .pNext = nullptr,
        .pApplicationName = "HelloVulkan",
        .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
        .pEngineName = "VulkanEngine",
        .engineVersion = VK_MAKE_VERSION(0, 0, 1),
        .apiVersion = VK_API_VERSION_1_2,
    };

    VkInstanceCreateInfo vkInfo{
        .pNext = nullptr,
        .pApplicationInfo = &appInfo,
    };

    VkInstance instance;
    if (auto result = vkCreateInstance(&vkInfo, nullptr, &instance); result != VK_SUCCESS) {
        LGL_LOGF("vkCreateInstance Error");
        return EXIT_FAILURE;
    }

    uint32_t physicalDeviceCount = 0;
    if (auto result = vkEnumeratePhysicalDeviceGroups(instance, &physicalDeviceCount, nullptr); result != VK_SUCCESS) {
        LGL_LOGF("vkEnumeratePhysicalDeviceGroups Error");
        return EXIT_FAILURE;
    }

    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    if (auto result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data()); result != VK_SUCCESS) {
        LGL_LOGF("vkEnumeratePhysicalDevices Error");
        return EXIT_FAILURE;
    }

    LGL_LOGD("Hello Vulkan");
    for (auto& device : physicalDevices) {
        static VkPhysicalDeviceProperties prop;
        static int index;
        vkGetPhysicalDeviceProperties(device, &prop);
        LGL_LOGI("Your Device[%d]: %s", index++, prop.deviceName);
    }

    vkDestroyInstance(instance, nullptr);
}