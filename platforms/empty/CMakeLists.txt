add_executable(empty EmptyApplication.cpp)

target_include_directories(empty PUBLIC ${PROJECT_SOURCE_DIR}/framework/common)

target_link_libraries(empty PRIVATE common)

