#pragma once
#include <cstdint>
#include "../../data/include/animators_database.h"

template <typename T>
struct SerializableComponent {
	EntityType type = Undefined;
	T component;

	SerializableComponent() = default;
	SerializableComponent(EntityType type, const T& component) : type(type), component(component){}
	
	template <typename Archive>
	void serialize(Archive& archive) {
		archive(type, component);
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
		component = AnimatorsDatabase::getInstance().fromTypeToAnimator(component.entityType);
	}
};