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

  LveWindow lveWindow{WIDTH, HEIGHT, "Alice 2D"};
  LveDevice lveDevice{lveWindow};
  LveRenderer lveRenderer{lveWindow, lveDevice};

  std::vector<Entity> entities;
  std::shared_ptr<PhysicsSystem> physicsSystem;
  Coordinator ecsCoordinator;
  
};
}  // namespace lve