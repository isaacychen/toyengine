#include <cstdio>
#include <exception>
#include "Application.h"

using namespace cj2engine;

namespace cj2engine {
    extern Application *app;
}

int main(int argc, char *argv[]) {


    try {
        app->init();
    } catch (const std::exception &e) {
        printf("App initialize failed, will exit now.");
        return 1;
    }

    while (!app->isQuit()) {
        app->update();
    }

    app->destroy();

    return 0;
}
