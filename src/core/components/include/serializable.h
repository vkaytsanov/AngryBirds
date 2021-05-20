#pragma once
#include <cstdint>
#include "../../data/include/animators_database.h"

template <typename T>
struct SerializableComponent {
	int64_t id = -1;
	T component;

	SerializableComponent() = default;
	SerializableComponent(int64_t id, const T& component) : id(id), component(component){}
	
	template <typename Archive>
	void serialize(Archive& archive) {
		archive(id, component);
	}
};

struct SerializableAnimatorComponent {
	int64_t id = -1;
	Animator component;

	SerializableAnimatorComponent() = default;
	SerializableAnimatorComponent(int64_t id, const Animator& component) : id(id), component(component){}
	
	template <typename Archive>
	void save(Archive& archive) {
		archive(id, component);
	}

	template <typename Archive>
	void load(Archive& archive) {
		archive(id, component);
		// getting the real component from the database, not just the type of it
		component = AnimatorsDatabase::getInstance().fromTypeToAnimator(component.prefabType);
	}
};