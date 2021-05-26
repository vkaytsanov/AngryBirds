#include "include/user_interface_system.h"
#include "include/lib.h"
#include "../components/2d/include/button.h"
#include "../components/2d/include/sprite.h"
#include "../components/include/transform.h"
#include "utils/include/viewport.h"


void UserInterfaceSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
}

void UserInterfaceSystem::configure(entityx::EventManager& events) {
}

void UserInterfaceSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events,
	entityx::TimeDelta dt) {
}

void UserInterfaceSystem::update(entityx::EntityManager& entities, entityx::EventManager& events,
                                 entityx::TimeDelta dt) {

	if(Lib::input->isMouseLeftClick()) {
		Vector2i mousePos = Viewport::fromScreenToViewport(Lib::input->getCurrMousePos());
		
		for(auto entity : entities.entities_with_components<Button>()) {
			auto transform = entity.getComponent<Transform>();
			auto sprite = entity.getComponent<Sprite>();

			if(isButtonHit(transform, sprite, mousePos)) {
				entity.getComponent<Button>()->clickListener();
				break;
			}
		}
	}
}

void UserInterfaceSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events,
	entityx::TimeDelta dt) {
}

bool UserInterfaceSystem::isButtonHit(entityx::ComponentHandle<Transform> transform,
                                      entityx::ComponentHandle<Sprite> sprite, Vector2i& mousePos) {

	float realWidth = static_cast<float>(sprite->m_textureRegion.getRegionWidth()) / SPRITE_DESCALE * transform->scale.x;
	float realHeight =  static_cast<float>(sprite->m_textureRegion.getRegionHeight()) / SPRITE_DESCALE * transform->scale.y;

#if defined(ORIGIN_IS_MIDDLE)
	float halfWidth = realWidth * 0.5f;
	float halfHeight = realHeight * 0.5f;

	if(mousePos.x >= transform->position.x - halfWidth && mousePos.x <= transform->position.x + halfWidth) {
		if(mousePos.y >= transform->position.y - halfHeight && mousePos.y <= transform->position.y + halfHeight) {
			return true;
		}
	}
#else
	Lib::app->error("UserInterfaceSystem", "Button Hit is not implemented for different camera origin");
#endif

	return false;
}