//
// Created by isaac on 5/31/2023.
//

#ifndef CJ2ENGINE_GLFWAPPLICATION_H
#define CJ2ENGINE_GLFWAPPLICATION_H

#include "BaseApplication.h"
#include "GLFW/glfw3.h"

namespace cj2engine {

    class GlfwApplication : public BaseApplication {

    private:
        GLFWwindow *window;

    public:
        GlfwApplication();

        ~GlfwApplication() override;

        void init() override;

        void update() override;

        void destroy() override;

        bool isQuit() override;

    };

}


#endif //CJ2ENGINE_GLFWAPPLICATION_H
