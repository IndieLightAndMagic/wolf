//
// Created by Guarin on 2019-08-04.
//

#ifndef WOLF_ENTITY_H
#define WOLF_ENTITY_H
#include <vector>
#include "Component.h"

namespace ECS_SYSTEM {

    class Entity;
    using PEntity = std::weak_ptr<ECS_SYSTEM::Entity>;
    class Entity {

    public:
        unsigned int componentInfoId;
        std::vector<unsigned int> componentIds;

    };
}
#endif //WOLF_ENTITY_H
