//
// Created by Viktor on 11.3.2021 г..
//

#include "include/transform_system.h"
#include "../components/include/transform.h"

void TransformSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	for(entityx::Entity entity : entities.entities_with_components<Transform>()){
		if(entity.getComponent<Transform>()->hasChanged){
			entityx::ComponentHandle<Transform> transform = entity.getComponent<Transform>();

			// rotation order Z -> Y -> X
			transform->rotation = Quaternionf().fromEulers(transform->eulerAngles.x * MathUtils::DEG2RADIANS, 0, 0) *
		                          Quaternionf().fromEulers(0, transform->eulerAngles.y * MathUtils::DEG2RADIANS, 0) *
		                          Quaternionf().fromEulers(0, 0, transform->eulerAngles.z * MathUtils::DEG2RADIANS);

			// Cache the transform matrix
			transform->transformMatrix = Matrix4f().setToTransform(transform->position, transform->rotation);

			// Update the entity right, up, forward vectors, normalized
			transform->right   = Vector3f(transform->transformMatrix[A00], transform->transformMatrix[A10], transform->transformMatrix[A20]).normalize();
			transform->up      = Vector3f(transform->transformMatrix[A01], transform->transformMatrix[A11], transform->transformMatrix[A21]).normalize();
			transform->forward = Vector3f(transform->transformMatrix[A02], transform->transformMatrix[A12], transform->transformMatrix[A22]).normalize();

			transform->hasChanged = false;
		}
	}
}
