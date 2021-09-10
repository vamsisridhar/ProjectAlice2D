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

  while (!lveWindow.shouldClose()) {
    glfwPollEvents();

    auto startTime = std::chrono::high_resolution_clock::now();

		physicsSystem->Update(dt, ecsCoordinator, mEntities);

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    
    if(auto commandBuffer = lveRenderer.beginFrame()){
      lveRenderer.beginSwapChainRenderPass(commandBuffer);
      simpleRenderSystem.renderGameObjects(commandBuffer, mEntities, ecsCoordinator);
      lveRenderer.endSwapChainRenderPass(commandBuffer);
      lveRenderer.endFrame();

    }
  }

  vkDeviceWaitIdle(lveDevice.device());
}

std::unique_ptr<LveModel> createCircleModel(LveDevice& device, unsigned int numSides) {
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
  return std::make_unique<LveModel>(device, vertices);
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

  
	std::vector<Entity> entities(MAX_ENTITIES);
  
 
  std::shared_ptr<LveModel> circleModel = createCircleModel(lveDevice, 64);

  Entity circle = ecsCoordinator.CreateEntity();

  ecsCoordinator.AddComponent(circle, Model{ .model = circleModel, .color = {.1f,.1f,.5f}});
  ecsCoordinator.AddComponent(circle, Transform{ .position = {.5f,.0f}, .scale =  {.1f,.1f}, .rotation = 0});
  ecsCoordinator.AddComponent(circle, RigidBody{.velocity={.0f,-.0001f}, .acceleration = {-.0001f, .0f}});

  entities[0] = circle;

  mEntities.resize(MAX_ENTITIES);
  mEntities = entities;
  


   /*
  auto circle = LveGameObject::createGameObject();
  circle.model = circleModel;
  circle.color = {.1f,.1f,.5f};
  circle.transform.scale = {.1f,.1f};
  circle.transform.translation = {.5f,.5f};

  gameObjects.push_back(std::move(circle));
  */

}

}  // namespace lve