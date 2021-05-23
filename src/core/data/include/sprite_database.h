#pragma once
#include "entity_type.h"
#include "../../components/2d/include/sprite.h"

class SpriteDatabase {
private:
	const std::array<Sprite, ENTITY_TYPE_SIZE> m_sprites;
public:
	SpriteDatabase();
	const Sprite& fromTypeToSprite(EntityType type) const;
	static SpriteDatabase& getInstance();
};
