#include "first_app.hpp"
#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
// std
#include <array>
#include <cassert>
#include <stdexcept>


namespace lve {

FirstApp::FirstApp() {
  loadGameObjects();
}

FirstApp::~FirstApp() { }

void FirstApp::run() {
  SimpleRenderSystem simpleRenderSystem{lveDevice, lveRenderer.getSwapChainRenderPass()};

  while (!lveWindow.shouldClose()) {
    glfwPollEvents();

    
    if (clockStarted)
    {
      stopTime = std::chrono::high_resolution_clock::now();
      dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
      clockStarted = false;
    }

    physicsSystem->Update(dt, ecsCoordinator, entities);

    if (!clockStarted)
    {
      startTime = std::chrono::high_resolution_clock::now();
      clockStarted = true;
    }

		


    
    if(auto commandBuffer = lveRenderer.beginFrame()){
      lveRenderer.beginSwapChainRenderPass(commandBuffer);
      simpleRenderSystem.renderGameObjects(commandBuffer, entities, ecsCoordinator);
      lveRenderer.endSwapChainRenderPass(commandBuffer);
      lveRenderer.endFrame();

    }
  }

  vkDeviceWaitIdle(lveDevice.device());
}


void FirstApp::loadGameObjects() {

  ecsCoordinator.Init();

  ecsCoordinator.RegisterComponent<RigidBody>();
  ecsCoordinator.RegisterComponent<Transform>();
  ecsCoordinator.RegisterComponent<Model>();

  auto physicsSystem = ecsCoordinator.RegisterSystem<PhysicsSystem>();

  Signature signature;
  signature.set(ecsCoordinator.GetComponentType<RigidBody>());
  signature.set(ecsCoordinator.GetComponentType<Transform>());
  signature.set(ecsCoordinator.GetComponentType<Model>());
  ecsCoordinator.SetSystemSignature<PhysicsSystem>(signature);
  
	entities.resize(MAX_ENTITIES);

  Primitive primitive{lveDevice, ecsCoordinator};

  entities[0] = primitive.Circle({.5f,.5f}, 0.1f, {.0f, .0f}, {.0f, -9.8f}, {.1f,.1f,.5f});
  entities[1] = primitive.Circle({-.5f,.5f}, 0.1f, {.0f, .0f}, {.0f, -9.8f}, {.5f,.1f,.5f});
  entities[2] = primitive.Circle({.0f,.5f}, 0.1f, {.0f, .0f}, {.0f, -9.8f}, {.1f,.5f,.5f});


}

}  // namespace lve