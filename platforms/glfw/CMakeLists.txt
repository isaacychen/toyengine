# Define your link libraries for different platforms
set(LINK_LIBRARIES_COMMON
        common
        glfw
        )

set(LINK_LIBRARIES_WINDOWS
        opengl32
        )

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
add_executable(glfw-app GlfwApplication.cpp)
target_include_directories(glfw-app PUBLIC ${PROJECT_SOURCE_DIR}/framework/common)
target_link_libraries(glfw-app PRIVATE ${LINK_LIBRARIES})
