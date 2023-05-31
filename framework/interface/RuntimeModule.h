//
// Created by isaac on 5/30/2023.
//

#ifndef CJ2ENGINE_RUNTIMEMODULE_H
#define CJ2ENGINE_RUNTIMEMODULE_H

namespace cj2engine {
    class RuntimeModule {
    public:
        virtual ~RuntimeModule() = default;
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void destroy() = 0;
    };
}

#endif //CJ2ENGINE_RUNTIMEMODULE_H
