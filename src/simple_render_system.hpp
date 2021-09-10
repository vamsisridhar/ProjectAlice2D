#pragma once

#include "lve_device.hpp"
#include "lve_pipeline.hpp"
//#include "lve_game_object.hpp"
#include "entity_components.hpp"
// std
#include <memory>
#include <vector>

namespace lve {
class SimpleRenderSystem {
 public:

  SimpleRenderSystem(LveDevice &device, VkRenderPass renderPass);
  ~SimpleRenderSystem();

  SimpleRenderSystem(const SimpleRenderSystem &) = delete;
  SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

  void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<Entity> &gameObjects, Coordinator &ecsCoordinator);

 private:
  void createPipelineLayout();
  void createPipeline(VkRenderPass renderPass);
  


  LveDevice& lveDevice;

  std::unique_ptr<LvePipeline> lvePipeline;
  VkPipelineLayout pipelineLayout;
};
}  // namespace lve