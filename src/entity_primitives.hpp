#pragma once

#include "entity_components.hpp"
#include "entity_models.hpp"
#include <vector>

namespace lve{

    class Primitive{

        public:

        Primitive(LveDevice &device, Coordinator &coordinator) : lveDevice{device}, ecsCoordinator{coordinator}{}


        Entity Circle(glm::vec2 pos, float radius, glm::vec2 vel, glm::vec2 acc, glm::vec3 color){
            ModelBuilder::MeshData circleModel = modelBuilder.createCircleModel(radius, 64, lveDevice);

            Entity circle = ecsCoordinator.CreateEntity();

            ecsCoordinator.AddComponent(circle, Model{ .model = circleModel.mesh,.vertices = circleModel.vertices, .color = color});
            ecsCoordinator.AddComponent(circle, Transform{ .position = pos, .scale =  {1.f, 1.f}, .rotation = 0});
            ecsCoordinator.AddComponent(circle, RigidBody{.velocity= vel, .acceleration = acc});

            return circle;
        }

        Entity Rect(glm::vec2 centrePos, float width, float height){
            ModelBuilder::MeshData rectModel = modelBuilder.createRectModel(width, height, lveDevice);

            Entity rect = ecsCoordinator.CreateEntity();

            ecsCoordinator.AddComponent(rect, Model{ .model = rectModel.mesh,.vertices = rectModel.vertices, .color = {1.f, 0.f, 0.f}});
            ecsCoordinator.AddComponent(rect, Transform{ .position = centrePos, .scale =  {0.5, 0.5}, .rotation = 0});
            ecsCoordinator.AddComponent(rect, RigidBody{.velocity= {0.f, 0.f}, .acceleration = {0.f, 0.f}});

            return rect;
        }


        private:

        LveDevice &lveDevice;
        Coordinator &ecsCoordinator;
        ModelBuilder modelBuilder;



    };

}