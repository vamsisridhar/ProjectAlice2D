#pragma once
#include "ecs_types.hpp"

#include <set>

namespace lve{

    class System{
        public:
        std::set<Entity> mEntities;
    };

}