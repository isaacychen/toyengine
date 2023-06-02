add_executable(hello-win WIN32 hello-win.cpp)
target_link_libraries(hello-win PRIVATE user32)
