#include "physics_system.hpp"
#include "entity_components.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/trigonometric.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
namespace lve{
    extern Coordinator ecsCoordinator;
    void PhysicsSystem::Init(){

    }
    void PhysicsSystem::Update(float dt, Coordinator &ecsCoordinator, std::vector<Entity> &mEntities)
    {
        for(auto const& entity: mEntities){
            
            if(entity != 0){
           
            auto& rigidBody = ecsCoordinator.GetComponent<RigidBody>(entity);

            auto& transform = ecsCoordinator.GetComponent<Transform>(entity);
            
            rigidBody.velocity += rigidBody.acceleration * dt;
            transform.position += rigidBody.velocity * dt;       

            if(std::strcmp(ecsCoordinator.GetComponent<Model>(entity).name, "Turny") == 0){
                ecsCoordinator.GetComponent<Transform>(entity).rotation += 0.1;
            }              
            
            }
        }
    }
}