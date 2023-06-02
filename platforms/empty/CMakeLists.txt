add_executable(empty-app EmptyApplication.cpp)

target_include_directories(empty-app PUBLIC ${PROJECT_SOURCE_DIR}/framework/common)

target_link_libraries(empty-app PRIVATE common)

