#pragma once

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "entityx/Entity.h"
#include "utils/include/animation.h"
#include "../../../data/include/prefab_database.h"

typedef std::function<void(entityx::Entity, int&)> StateHandler;

class Animator : public entityx::Component<Animator> {
public:
	int currentAnimation = 0;
	// the assigned animations 
	std::vector<Animation> animations;
	// instead of a state machine class, we use lambda functions
	// which encapsulates their own logic for
	// what to be the next animation type
	// #conditions.size() must be equal to #animations.size()
	std::vector<StateHandler> conditions;

	// Serialization
	PrefabType prefabType = Undefined;
	
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
	archive(prefabType);
}

template <typename Archive>
void Animator::load(Archive& archive) {
	// loading only the type of the prefab
	archive(prefabType);
	// will load the real in the SerializeComponent<Animator>
}



#endif
