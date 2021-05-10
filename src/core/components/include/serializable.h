#pragma once
#include <cstdint>

template <typename T>
struct SerializableComponent {
	int64_t id;
	T component;

	SerializableComponent() = default;
	SerializableComponent(int64_t id, const T& component) : id(id), component(component){}
	
	template <typename Archive>
	void serialize(Archive& archive) {
		archive(id, component);
	}
};