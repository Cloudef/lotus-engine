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
        void tick_all(time_point time, duration delta)
        {
            tick(time, delta);
            for (const auto& entity : entities)
            {
                entity->tick_all(time, delta);
            }
        }
        template <typename T, typename... Args>
        std::shared_ptr<T> AddEntity(Args... args)
        {
            auto sp = std::static_pointer_cast<T>(entities.emplace_back(std::make_shared<T>()));
            sp->Init(sp, engine, args...);
            RebuildTLAS();
            return sp;
        }
    protected:
        virtual void tick(time_point time, duration delta) {}
        void RebuildTLAS();

        Engine* engine;
        std::vector<std::shared_ptr<TopLevelAccelerationStructure>> top_level_as;
        bool rebuild_as{ false };
        std::vector<std::shared_ptr<Entity>> entities;
    };
}