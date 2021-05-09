#include "include/pigs_db.h"

#include "include/asset_manager.h"
#include "../components/include/sprite.h"
#include "../components/include/circle_collider.h"
#include "../components/include/transform.h"

PigsDB::PigsDB(entityx::EntityManager& entityManager) {
	const Texture* spriteSheet = AssetManager::getInstance().getSprite("pigs");

	auto normalPig = entityManager.create();
	normalPig.addComponent<Transform>();
	normalPig.addComponent<Sprite>(TextureRegion(spriteSheet, 679, 790, 99, 97));
	// normalPig.addComponent<CircleCollider>(1.0f);
}
