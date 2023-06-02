//
// Created by isaac on 5/30/2023.
//

#ifndef CJ2ENGINE_BASEAPPLICATION_H
#define CJ2ENGINE_BASEAPPLICATION_H

#include "Application.h"

namespace cj2engine {

    class BaseApplication : public Application {
    private:
        bool quit = false;

    public:
        void init() override;

        void update() override;

        void destroy() override;

        bool isQuit() override;
    };
}

#endif //CJ2ENGINE_BASEAPPLICATION_H
