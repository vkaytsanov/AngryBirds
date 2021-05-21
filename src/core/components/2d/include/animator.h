#pragma once

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "entityx/Entity.h"
#include "utils/include/animation.h"
#include "../../../data/include/entity_type.h"

typedef std::function<void(entityx::Entity, int&)> StateHandler;

struct Animator : public entityx::Component<Animator> {
	int currentAnimation = 0;
	// the assigned animations 
	std::vector<Animation> animations;
	// instead of a state machine class, we use lambda functions
	// which encapsulates their own logic for
	// what to be the next animation type
	// #conditions.size() must be equal to #animations.size()
	std::vector<StateHandler> conditions;

	// Serialization
	EntityType entityType = Undefined;
	
	Animator() = default;
	Animator(const Animator& other) = default;
	Animator(std::vector<Animation>& animations);
	Animator(std::vector<Animation>&& animations);

	Sprite& getFrame();

	template<typename Archive>
	inline void save(Archive& archive);
	
	template<typename Archive>
	inline void load(Archive& archive);
};


template <typename Archive>
void Animator::save(Archive& archive) {
	archive(entityType);
}

template <typename Archive>
void Animator::load(Archive& archive) {
	// loading only the type of the prefab
	archive(entityType);
	// will load the real in the SerializeComponent<Animator>
}



#endif
