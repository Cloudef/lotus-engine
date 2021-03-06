#pragma once
#include "entity/entity.h"
#include <memory>
#include <vector>
#include "renderer/acceleration_structure.h"

namespace lotus
{
    class Engine;

    class Scene
    {
    public:
        explicit Scene(Engine* _engine);
        void render();
        void tick_all(time_point time, duration delta);
        template <typename T, typename... Args>
        std::shared_ptr<T> AddEntity(Args... args)
        {
            auto sp = std::static_pointer_cast<T>(new_entities.emplace_back(std::make_shared<T>(engine)));
            sp->Init(sp, args...);
            return sp;
        }
        template<typename F>
        void forEachEntity(F func)
        {
            for(auto& entity : entities)
            {
                func(entity);
            }
        }
        std::vector<std::shared_ptr<TopLevelAccelerationStructure>> top_level_as;
    protected:
        virtual void tick(time_point time, duration delta) {}

        Engine* engine;
        std::vector<std::shared_ptr<Entity>> entities;
        std::vector<std::shared_ptr<Entity>> new_entities;
    };
}
