#include "physics_system.hpp"
#include "entity_components.hpp"

namespace lve{
    extern Coordinator ecsCoordinator;
    void PhysicsSystem::Init(){

    }
    void PhysicsSystem::Update(float dt, Coordinator &ecsCoordinator, std::vector<Entity> &mEntities)
    {
        for(auto const& entity: mEntities){
            auto& rigidBody = ecsCoordinator.GetComponent<RigidBody>(entity);
            auto& transform = ecsCoordinator.GetComponent<Transform>(entity);

            transform.position += rigidBody.velocity * dt;

        }
    }
}