#pragma once

#include<glm/gtc/matrix_transform.hpp>
#include "ECS\ecs_coordinator.hpp"
#include "lve_model.hpp"
#include <memory>

namespace lve{

    

    struct Model
    {
        std::shared_ptr<LveModel> model{};
        glm::vec3 color{};
    };
    
    struct Transform
    {
        glm::vec2 position{};
        glm::vec2 scale{1.f, 1.f};
        float rotation;

        glm::mat2 mat2() {
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotMatrix{{c, s}, {-s, c}};

            glm::mat2 scaleMat{{scale.x, .0f}, {.0f, scale.y}};
            return rotMatrix * scaleMat;
        }
    };

    struct RigidBody
    {
        glm::vec2 velocity{};
        glm::vec2 acceleration{};
    };

}