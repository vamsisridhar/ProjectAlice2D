#pragma once

#include "lve_device.hpp"
#include "lve_window.hpp"
#include "lve_renderer.hpp"
#include "entity_components.hpp"
#include "ECS\ecs_coordinator.hpp"
#include "physics_system.hpp"
// std
#include <memory>
#include <vector>

namespace lve {

class FirstApp {
 public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 800;

  FirstApp();
  ~FirstApp();

  FirstApp(const FirstApp &) = delete;
  FirstApp &operator=(const FirstApp &) = delete;

  void run();

 private:
  void loadGameObjects();

  LveWindow lveWindow{WIDTH, HEIGHT, "Vulkan Tutorial"};
  LveDevice lveDevice{lveWindow};
  LveRenderer lveRenderer{lveWindow, lveDevice};

  float dt = 0.0f;

  std::vector<Entity> mEntities;
  std::shared_ptr<PhysicsSystem> physicsSystem;
  Coordinator ecsCoordinator;

  //std::vector<LveGameObject> gameObjects;

  
};
}  // namespace lve