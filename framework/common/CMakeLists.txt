add_library(common
        main.cpp
        BaseApplication.cpp
        GraphicsManager.cpp
        )

target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/framework/interface)
