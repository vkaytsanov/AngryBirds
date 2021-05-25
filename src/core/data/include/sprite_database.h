#pragma once
#include <array>

#include "entity_type.h"
#include "../../components/2d/include/sprite.h"

class SpriteDatabase {
private:
	std::array<Sprite, ENTITY_TYPE_SIZE> m_sprites;
	Sprite m_groundSprite;
	Sprite m_backgroundSprite;
	Sprite m_frontSlingshotSprite;
	Sprite m_backSlingshotSprite;
public:
	SpriteDatabase();
	~SpriteDatabase();
public:
	const Sprite& fromTypeToSprite(EntityType type) const;
	const Sprite& getGround();
	const Sprite& getBackground();
	const Sprite& getFrontSlingshot();
	const Sprite& getBackSlingshot();
	static SpriteDatabase& getInstance();
};
