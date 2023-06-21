//
// Created by isaac on 6/16/2023.
//

#ifndef CJ2ENGINE_HELLOTRIANGLEAPPLICATION_H
#define CJ2ENGINE_HELLOTRIANGLEAPPLICATION_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace cj2ware {

    class HelloTriangleApplication {
    public:
        void run();

    private:
        GLFWwindow *window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;

        void initWindow();

        void initVulkan();

        void mainLoop();

        void cleanup() noexcept;

        void createInstance();

        static bool checkValidationLayerSupport();

        static std::vector<const char *> getRequiredExtensions();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData);

        void setupDebugMessenger();

        static VkResult createDebugUtilsMessengerEXT(VkInstance instance,
                                                     const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                                     const VkAllocationCallbacks *pAllocator,
                                                     VkDebugUtilsMessengerEXT *pDebugMessenger);

        static void destroyDebugUtilsMessengerEXT(VkInstance instance,
                                                  VkDebugUtilsMessengerEXT debugMessenger,
                                                  const VkAllocationCallbacks *pAllocator);

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    };

}


#endif //CJ2ENGINE_HELLOTRIANGLEAPPLICATION_H
