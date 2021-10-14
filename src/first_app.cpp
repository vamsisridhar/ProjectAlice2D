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
#include <chrono>


namespace lve {

FirstApp::FirstApp() {
  loadGameObjects();
}

FirstApp::~FirstApp() { }

void FirstApp::run() {
  SimpleRenderSystem simpleRenderSystem{lveDevice, lveRenderer.getSwapChainRenderPass()};

  auto currentTime = std::chrono::high_resolution_clock::now();

  while (!lveWindow.shouldClose()) {
    glfwPollEvents();

    auto newTime = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
    currentTime = newTime;


    physicsSystem->Update(0.01, ecsCoordinator, entities);



		


    
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

  entities[0] = primitive.Circle({.5f,-.2f}, 0.1f, {.0f, .0f}, {.0f,-0.98f}, {.1f,.1f,.5f});
  entities[1] = primitive.Circle({.0f,.0f}, 0.1f, {.0f, .0f}, {.0f, .0f}, {.5f,.1f,.5f});
  //entities[2] = primitive.Circle({.0f,.5f}, 0.1f, {.0f, .0f}, {.0f, -9.8f}, {.1f,.5f,.5f});
  entities[3] = primitive.Line({.5f, .5f}, 2.f, 0, "Pointer" ,{1.f, 0.f, 0.f});
  entities[4] = primitive.Line({.5f, .5f}, 2.f, 355, "Turny");


}

}  // namespace lve