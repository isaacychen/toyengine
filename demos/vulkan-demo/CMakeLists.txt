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

# 查找GLSL编译器
find_program(GLSLC glslc)
if(NOT GLSLC)
    message(FATAL_ERROR "GLSLC compiler not found!")
endif()

set(SHADER_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/shaders)  # 设置你的GLSL文件列表
# 自定义命令：编译GLSL文件为SPIR-V
file(GLOB SHADER_FILES ${SHADER_FOLDER}/*.vert ${SHADER_FOLDER}/*.frag)

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME)
    set(SPIRV_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER_NAME}.spv)
    add_custom_command(
            OUTPUT ${SPIRV_OUTPUT}
            COMMAND ${GLSLC} -o ${SPIRV_OUTPUT} ${SHADER_FILE}
            MAIN_DEPENDENCY ${SHADER_FILE}
            COMMENT "Compiling ${SHADER_FILE} to ${SPIRV_OUTPUT}"
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV_OUTPUT})
endforeach()

## 添加可执行文件，并将GLSL编译为SPIR-V作为依赖项
#add_executable(shaders ${SOURCE_FILES} ${SPIRV_BINARY_FILES})

add_custom_target(shaders DEPENDS ${SPIRV_BINARY_FILES})  # 创建一个自定义目标以便在构建过程中生成SPIR-V文件

add_dependencies(vulkan-demo shaders)
