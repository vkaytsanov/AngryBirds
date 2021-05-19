#pragma once

#include "entityx/Entity.h"
#include "utils/include/animation.h"

typedef std::function<void(entityx::Entity, int&)> ConditionalDef;

struct Animator : public entityx::Component<Animator> {
	int currentAnimation = 0;
	// the assigned animations 
	std::vector<Animation> animations;
	// instead of a state machine class, we use lambda functions
	// which encapsulates their own logic for
	// what to be the next animation type
	// #conditions.size() must be equal to #animations.size()
	std::vector<ConditionalDef> conditions;
	
	Animator() = default;
	Animator(std::vector<Animation>& animations);
	Animator(std::vector<Animation>&& animations);

	Sprite& getFrame();
};

