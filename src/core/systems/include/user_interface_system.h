#pragma once
#include "entityx/System.h"
#include "utils/geometry/include/vector2.h"

struct Transform;
class Sprite;

class UserInterfaceSystem : public entityx::System<UserInterfaceSystem> {
private:
	bool isButtonHit(entityx::ComponentHandle<Transform> transform, entityx::ComponentHandle<Sprite> sprite, Vector2i& mousePos);
public:
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};
