#pragma once

#include <memory>
#include <bitset>

namespace lve{
    //ECS CONSTS
    //ECS IMPLEMENTATION USED: https://austinmorlan.com/posts/entity_component_system/
    using Entity = std::uint32_t;
    const Entity MAX_ENTITIES = 5000;
    using ComponentType = std::uint8_t;
    const ComponentType MAX_COMPONENTS = 32;
    using Signature = std::bitset<MAX_COMPONENTS>;
}