//
// Created by isaac on 5/30/2023.
//

#include "BaseApplication.h"
#include <cstdio>

namespace cj2engine {

    void BaseApplication::init() {
        quit = false;
    }

    void BaseApplication::update() {
        printf("Hello, World!\n");
        quit = true;
    }

    void BaseApplication::destroy() {

    }

    bool BaseApplication::isQuit() {
        return quit;
    }

}
