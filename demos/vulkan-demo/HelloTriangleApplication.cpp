//
// Created by isaac on 6/16/2023.
//

#include "HelloTriangleApplication.h"

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <stdexcept>
#include <iostream>
#include <ranges>

const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace cj2ware {

    void HelloTriangleApplication::run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    void HelloTriangleApplication::initWindow() {
        /* Initialize the library */
        if (!glfwInit()) throw std::runtime_error("glfwInit failed!");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
    }

    void HelloTriangleApplication::initVulkan() {
        createInstance();
        setupDebugMessenger();
//    uint32_t extensionCount = 0;
//    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//
//    std::cout << extensionCount << " extensions supported\n";
//
//    glm::mat4 matrix;
//    glm::vec4 vec;
//    auto test = matrix * vec;
    }

    void HelloTriangleApplication::createInstance() {

        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

//    uint32_t glfwExtensionCount = 0;
//    const char **glfwExtensions;
//    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//
//    createInfo.enabledExtensionCount = glfwExtensionCount;
//    createInfo.ppEnabledExtensionNames = glfwExtensions;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
        }

//    uint32_t extensionCount = 0;
//    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//    std::vector<VkExtensionProperties> extensions(extensionCount);
//    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
//
//    std::cout << "available extensions:\n";
//    for (const auto &extension: extensions) {
//        std::cout << '\t' << extension.extensionName << '\n';
//    }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            std::cerr << "vkCreateInstance failed with error code: " << result << std::endl;
            throw std::runtime_error("failed to create instance!");
        }

    }

    void HelloTriangleApplication::mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void HelloTriangleApplication::cleanup() noexcept {
        if (enableValidationLayers) {
            destroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool HelloTriangleApplication::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        auto matchedLayers =
                availableLayers | std::views::filter([](const VkLayerProperties &layer) {
                    return std::ranges::find_if(validationLayers, [&layer](const char *layerName) {
                        return strcmp(layer.layerName, layerName) == 0;
                    }) != validationLayers.end();
                });

        std::cout << "Available layers:\n";
        for (const auto &layer: availableLayers) {
            std::cout << '\t' << layer.layerName << '\n';
        }

        return !matchedLayers.empty();
    }

    std::vector<const char *> HelloTriangleApplication::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    VkBool32 HelloTriangleApplication::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                     VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                     const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                     void *pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }

    void HelloTriangleApplication::setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        populateDebugMessengerCreateInfo(createInfo);

        if (createDebugUtilsMessengerEXT(instance, &createInfo, nullptr,
                                         &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    VkResult HelloTriangleApplication::createDebugUtilsMessengerEXT(VkInstance instance,
                                                                    const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                                                    const VkAllocationCallbacks *pAllocator,
                                                                    VkDebugUtilsMessengerEXT *pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                               "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void HelloTriangleApplication::destroyDebugUtilsMessengerEXT(VkInstance instance,
                                                                 VkDebugUtilsMessengerEXT debugMessenger,
                                                                 const VkAllocationCallbacks *pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                                "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    void HelloTriangleApplication::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }

}
