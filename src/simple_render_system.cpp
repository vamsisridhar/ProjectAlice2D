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

struct SimplePushConstantData {
  glm::mat2 transform{1.f};
  glm::vec2 offset;
  alignas(16) glm::vec3 color;
};

SimpleRenderSystem::SimpleRenderSystem(LveDevice &device, VkRenderPass renderPass) : lveDevice{device} {
  createPipelineLayout();
  createPipeline(renderPass);
}

SimpleRenderSystem::~SimpleRenderSystem() { vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr); }


void SimpleRenderSystem::createPipelineLayout() {

  VkPushConstantRange pushConstantRange{};
  pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT|VK_SHADER_STAGE_FRAGMENT_BIT;
  pushConstantRange.offset = 0;
  pushConstantRange.size = sizeof(SimplePushConstantData);

  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 1;
  pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
  if (vkCreatePipelineLayout(lveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create pipeline layout!");
  }
}

void SimpleRenderSystem::createPipeline(VkRenderPass renderPass) {
  assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

  PipelineConfigInfo pipelineConfig{};
  LvePipeline::defaultPipelineConfigInfo(pipelineConfig);
  pipelineConfig.renderPass = renderPass;
  pipelineConfig.pipelineLayout = pipelineLayout;
  lvePipeline = std::make_unique<LvePipeline>(
      lveDevice,
      "..\\src\\shaders\\simple_shader.vert.spv",
      "..\\src\\shaders\\simple_shader.frag.spv",
      pipelineConfig);
}


void SimpleRenderSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<Entity> &entities, Coordinator &ecsCoordinator){
  lvePipeline->bind(commandBuffer);
  for (auto&entity:entities){
    if (entity != 0){

    SimplePushConstantData push{};
    push.offset = {ecsCoordinator.GetComponent<Transform>(entity).position.x, -ecsCoordinator.GetComponent<Transform>(entity).position.y};
    push.color = ecsCoordinator.GetComponent<Model>(entity).color;
    push.transform = ecsCoordinator.GetComponent<Transform>(entity).mat2();

    vkCmdPushConstants(
      commandBuffer, 
      pipelineLayout, 
      VK_SHADER_STAGE_VERTEX_BIT|VK_SHADER_STAGE_FRAGMENT_BIT, 
      0, 
      sizeof(SimplePushConstantData), 
      &push);

    ecsCoordinator.GetComponent<Model>(entity).model->bind(commandBuffer);
    ecsCoordinator.GetComponent<Model>(entity).model->draw(commandBuffer);
    }
  }
}

}  // namespace lve