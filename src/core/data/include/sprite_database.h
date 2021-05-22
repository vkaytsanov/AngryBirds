#pragma once
#include "entity_type.h"
#include "../../components/2d/include/sprite.h"

class SpriteDatabase {
private:
	std::array<Sprite, ENTITY_TYPE_SIZE> m_sprites;
public:
	SpriteDatabase();
	Sprite& fromTypeToSprite(EntityType type);
	static SpriteDatabase& getInstance();
};
