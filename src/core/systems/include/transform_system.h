//
// Created by Viktor on 11.3.2021 г..
//

#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H


#include "../../../lib/entityx/System.h"

class TransformSystem : public entityx::System<TransformSystem>{
public:
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};


#endif //TRANSFORM_SYSTEM_H
