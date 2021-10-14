#pragma once
#include "ECS\ecs_system.hpp"
#include "ECS\ecs_coordinator.hpp"
#include "entity_models.hpp"

namespace lve{

    class PhysicsSystem:public System{

        public:
        void Init();

        void Update(float dt, Coordinator &ecsCoordinator, std::vector<Entity> &mEntities);

        ModelBuilder modelBuilder{};
    };

}