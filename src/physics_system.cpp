#include "physics_system.hpp"
#include "entity_components.hpp"
#include <iostream>
#include <algorithm>
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

            //collision

            for(auto const& target: mEntities)

                if(target != 0 && target != entity){
                    
                    auto& entityMesh = ecsCoordinator.GetComponent<Model>(entity).vertices;
                    auto& targetMesh = ecsCoordinator.GetComponent<Model>(target).vertices;

                    auto& entityPos = ecsCoordinator.GetComponent<Transform>(entity).position;
                    auto& targetPos = ecsCoordinator.GetComponent<Transform>(target).position;

                    for (int i = 0; i < entityMesh.size()/3; i++)
                    {
                        float yVertexPosListEntity[] = {entityMesh[i*3].position.y, entityMesh[i*3 + 1].position.y , entityMesh[i*3 + 2].position.y};
                        float xVertexPosListEntity[] = {entityMesh[i*3].position.x, entityMesh[i*3 + 1].position.x , entityMesh[i*3 + 2].position.x};
                        float yMaxEntity = entityPos.y + *std::max_element(yVertexPosListEntity, yVertexPosListEntity + 3);
                        float xMaxEntity = entityPos.x + *std::max_element(xVertexPosListEntity, xVertexPosListEntity + 3);
                        float yMinEntity = entityPos.y + *std::min_element(yVertexPosListEntity, yVertexPosListEntity + 3);
                        float xMinEntity = entityPos.x + *std::min_element(xVertexPosListEntity, xVertexPosListEntity + 3);

                        for (int j = 0; j < targetMesh.size()/3; j++){
                            float yVertexPosListTarget[] = {targetMesh[i*3].position.y, targetMesh[i*3 + 1].position.y , targetMesh[i*3 + 2].position.y};
                            float xVertexPosListTarget[] = {targetMesh[i*3].position.x, targetMesh[i*3 + 1].position.x , targetMesh[i*3 + 2].position.x};
                            float yMaxTarget = targetPos.y + *std::max_element(yVertexPosListTarget, yVertexPosListTarget + 3);
                            float xMaxTarget = targetPos.x + *std::max_element(xVertexPosListTarget, xVertexPosListTarget + 3);
                            float yMinTarget = targetPos.y + *std::min_element(yVertexPosListTarget, yVertexPosListTarget + 3);
                            float xMinTarget = targetPos.x + *std::min_element(xVertexPosListTarget, xVertexPosListTarget + 3);

                            if ((yMinEntity < yMaxTarget && yMaxEntity > yMinTarget)|| (yMaxEntity > yMinTarget && yMinEntity < yMinTarget))
                            {
                                if((xMinEntity < xMaxTarget && xMaxEntity > xMinTarget)|| (xMaxEntity > xMinTarget && xMinEntity < xMinTarget)){
                                    std::cout << "Collision between Entity " << entity << " and Target " << target << std::endl;
                                    
                                    break;
                                }
                            }
                            
                        }
                    }
                    


                }
            
            }
        }
    }
}