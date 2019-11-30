#pragma once

#include "entity.h"

#include <memory>
#include "engine/renderer/model.h"
#include "engine/renderer/skeleton.h"

namespace lotus
{
    class AnimationComponent;
    class RenderableEntity : public Entity
    {
    public:

        struct UniformBufferObject {
            glm::mat4 model;
            glm::mat4 modelIT;
        };

        RenderableEntity();
        virtual ~RenderableEntity() = default;

        void setScale(float x, float y, float z);

        void addSkeleton(std::unique_ptr<Skeleton>&& skeleton, Engine* engine, size_t vertex_stride);

        virtual void populate_AS(TopLevelAccelerationStructure* as, uint32_t image_index);
        virtual void update_AS(TopLevelAccelerationStructure* as, uint32_t image_index);

        std::vector<std::shared_ptr<Model>> models;

        glm::mat4 getModelMatrix();

        std::unique_ptr<Buffer> uniform_buffer;
        std::vector<vk::UniqueHandle<vk::CommandBuffer, vk::DispatchLoaderDynamic>> command_buffers;
        std::vector<vk::UniqueHandle<vk::CommandBuffer, vk::DispatchLoaderDynamic>> shadowmap_buffers;
        AnimationComponent* animation_component {nullptr};

    protected:
        virtual void render(Engine* engine, std::shared_ptr<Entity>& sp) override;
        glm::vec3 scale{ 1.f, 1.f, 1.f };
        glm::mat4 scale_mat{ 1.f };
    };
}
