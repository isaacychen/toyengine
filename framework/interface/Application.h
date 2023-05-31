//
// Created by isaac on 5/30/2023.
//

#ifndef CJ2ENGINE_APPLICATION_H
#define CJ2ENGINE_APPLICATION_H

#include "RuntimeModule.h"

namespace cj2engine {
    class Application: public RuntimeModule{
    public:
        virtual bool isQuit() = 0;
    };
}

#endif //CJ2ENGINE_APPLICATION_H
