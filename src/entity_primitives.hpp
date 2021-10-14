#pragma once

#include "entity_components.hpp"
#include "entity_models.hpp"
#include <vector>

namespace lve{

    class Primitive{

        public:

        Primitive(LveDevice &device, Coordinator &coordinator) : lveDevice{device}, ecsCoordinator{coordinator}{}


        Entity Circle(glm::vec2 pos, float radius, glm::vec2 vel, glm::vec2 acc, glm::vec3 color, const char* name = "Circle"){
            ModelBuilder::MeshData circleModel = modelBuilder.createCircleModel(radius, 64, name, lveDevice);

            Entity circle = ecsCoordinator.CreateEntity();

            //circleModel.vertices = modelBuilder.increaseResolution(circleModel.vertices, 0, circleModel.resolution);

            ecsCoordinator.AddComponent(circle, Model{ .model = circleModel.mesh, .resolution = circleModel.resolution, .color = color,.type="Circle", .name=name});
            ecsCoordinator.AddComponent(circle, Transform{ .position = pos, .scale =  {1.f, 1.f}, .rotation = 0});
            ecsCoordinator.AddComponent(circle, RigidBody{.velocity= vel, .acceleration = acc});

            return circle;
        }

        Entity Rect(glm::vec2 centrePos, float width, float height, const char* name = "Rect"){
            ModelBuilder::MeshData rectModel = modelBuilder.createRectModel(width, height,name, lveDevice);

            Entity rect = ecsCoordinator.CreateEntity();
            
            //rectModel.vertices = modelBuilder.increaseResolution(rectModel.mesh, 0, rectModel.resolution);

            ecsCoordinator.AddComponent(rect, Model{ .model = rectModel.mesh,.resolution = rectModel.resolution, .color = {1.f, 0.f, 0.f},.type="Rect", .name =name});
            ecsCoordinator.AddComponent(rect, Transform{ .position = centrePos, .scale =  {0.5, 0.5}, .rotation = 0});
            ecsCoordinator.AddComponent(rect, RigidBody{.velocity= {0.f, 0.f}, .acceleration = {0.f, 0.f}});

            return rect;
        }

        Entity Line(glm::vec2 pivotPoint, float scale,  float angle, const char* name = "Line", glm::vec3 color = {1.f, 1.f, 1.f}){

            ModelBuilder::MeshData lineModel = modelBuilder.createLineModel(scale, angle * (glm::pi<float>()/180),name, lveDevice);

            Entity line = ecsCoordinator.CreateEntity();

            ecsCoordinator.AddComponent(line, Model{ .model = lineModel.mesh,.resolution = lineModel.resolution, .color = color,.type="Line", .name=name});
            ecsCoordinator.AddComponent(line, Transform{ .position = pivotPoint, .scale =  {0.5, 0.5}, .rotation = 0});
            ecsCoordinator.AddComponent(line, RigidBody{.velocity= {0.f, 0.f}, .acceleration = {0.f, 0.f}});

            return line;
        }


        private:

        LveDevice &lveDevice;
        Coordinator &ecsCoordinator;
        ModelBuilder modelBuilder;



    };

}