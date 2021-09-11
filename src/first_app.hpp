#pragma once

#include "lve_device.hpp"
#include "lve_window.hpp"
#include "lve_renderer.hpp"
#include "entity_primitives.hpp"
#include "ECS\ecs_coordinator.hpp"
#include "physics_system.hpp"
// std
#include <memory>
#include <vector>
#include <chrono>

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
  bool clockStarted = false;
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::high_resolution_clock::time_point stopTime;

  std::vector<Entity> entities;
  std::shared_ptr<PhysicsSystem> physicsSystem;
  Coordinator ecsCoordinator;

  //std::vector<LveGameObject> gameObjects;

  
};
}  // namespace lve