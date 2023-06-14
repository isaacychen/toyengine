add_executable(tiny-renderer
        main.cpp
        tgaimage.cpp
        model.cpp
        cj2math.cpp)

# 复制resources目录到输出目录的自定义命令
add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
        COMMENT "Copying assets directory"
        VERBATIM
        )

# 添加依赖，使得每次构建时都会重新复制资源文件
add_dependencies(tiny-renderer copy_assets)
