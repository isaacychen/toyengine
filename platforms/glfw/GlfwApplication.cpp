//
// Created by isaac on 5/31/2023.
//

#include <stdexcept>
#include "GlfwApplication.h"

namespace cj2engine {

    GlfwApplication glfwApp;
    Application *app = &glfwApp;

    GlfwApplication::GlfwApplication() {
        window = nullptr;
    }

    GlfwApplication::~GlfwApplication() {
        if (window) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    void GlfwApplication::init() {
        /* Initialize the library */
        if (!glfwInit())
            throw std::runtime_error("glfwInit failed");

        window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow failed");
        }

        glfwMakeContextCurrent(window);
    }

    void GlfwApplication::update() {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    void GlfwApplication::destroy() {
        glfwTerminate();
    }

    bool GlfwApplication::isQuit() {
        return glfwWindowShouldClose(window);
    }

}
