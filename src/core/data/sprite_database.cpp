#include "include/sprite_database.h"

SpriteDatabase::SpriteDatabase() {
	const std::shared_ptr<Texture> animatedTexture = AssetManager::getInstance().getSprite("all-in-one");
	
	m_sprites[Terence	] = Sprite(TextureRegion(animatedTexture), true);
	m_sprites[Red		] = Sprite(TextureRegion(animatedTexture), true);
	m_sprites[Chuck		] = Sprite(TextureRegion(animatedTexture), true);
	m_sprites[JayJakeJim] = Sprite(TextureRegion(animatedTexture), true);
	m_sprites[PigMinion ] = Sprite(TextureRegion(animatedTexture), true);

	const std::shared_ptr<Texture> blocksTexture = AssetManager::getInstance().getSprite("blocks");

	m_sprites[WoodTriangle ] = Sprite(TextureRegion(blocksTexture, 874, 0, 82, 82));
	m_sprites[WoodSquare   ] = Sprite(TextureRegion(blocksTexture, 709, 0, 82, 82));
	m_sprites[WoodRectangle] = Sprite(TextureRegion(blocksTexture, 314, 614, 200, 20));           
}

Sprite& SpriteDatabase::fromTypeToSprite(EntityType type) {
	return m_sprites[type];
}

SpriteDatabase& SpriteDatabase::getInstance() {
	static SpriteDatabase database;
	return database;
}
