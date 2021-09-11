#pragma once

#include "entity_components.hpp"

namespace lve{

    class Primitive{

        public:

        Primitive(LveDevice &device, Coordinator &coordinator) : lveDevice{device}, ecsCoordinator{coordinator}{}

        std::unique_ptr<LveModel> createCircleModel(unsigned int numSides) {
            std::vector<LveModel::Vertex> uniqueVertices{};
            for (int i = 0; i < numSides; i++) {
                float angle = i * glm::two_pi<float>() / numSides;
                uniqueVertices.push_back({{glm::cos(angle), glm::sin(angle)}});
            }
            uniqueVertices.push_back({});  // adds center vertex at 0, 0
            
            std::vector<LveModel::Vertex> vertices{};
            for (int i = 0; i < numSides; i++) {
                vertices.push_back(uniqueVertices[i]);
                vertices.push_back(uniqueVertices[(i + 1) % numSides]);
                vertices.push_back(uniqueVertices[numSides]);
            }
            return std::make_unique<LveModel>(lveDevice, vertices);
        }

        Entity Circle(glm::vec2 pos, float radius, glm::vec2 vel, glm::vec2 acc, glm::vec3 color){
            std::shared_ptr<LveModel> circleModel = createCircleModel(64);

            Entity circle = ecsCoordinator.CreateEntity();

            ecsCoordinator.AddComponent(circle, Model{ .model = circleModel, .color = color});
            ecsCoordinator.AddComponent(circle, Transform{ .position = pos, .scale =  {radius, radius}, .rotation = 0});
            ecsCoordinator.AddComponent(circle, RigidBody{.velocity= vel, .acceleration = acc});

            return circle;
        }

        private:

        LveDevice &lveDevice;
        Coordinator &ecsCoordinator;



    };

}