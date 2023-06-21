find_package(Vulkan REQUIRED)

# Define your link libraries for different platforms
set(LINK_LIBRARIES_COMMON
        glm
        glfw
        ${Vulkan_LIBRARIES}
        )

#set(LINK_LIBRARIES_WINDOWS
#        vulkan-1
#        )

#set(LINK_LIBRARIES_MACOS
#        library_macos
#        )
#
#set(LINK_LIBRARIES_LINUX
#        library_linux
#        )

# Conditionally add the platform-specific link libraries based on the target platform
if(WIN32)
    set(LINK_LIBRARIES ${LINK_LIBRARIES_COMMON} ${LINK_LIBRARIES_WINDOWS})
elseif(APPLE)
    set(LINK_LIBRARIES ${LINK_LIBRARIES_COMMON} ${LINK_LIBRARIES_MACOS})
else()
    set(LINK_LIBRARIES ${LINK_LIBRARIES_COMMON} ${LINK_LIBRARIES_LINUX})
endif()

# Create your executable or library target
add_executable(vulkan-demo main.cpp HelloTriangleApplication.cpp)
target_include_directories(vulkan-demo PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(vulkan-demo PRIVATE ${LINK_LIBRARIES})
