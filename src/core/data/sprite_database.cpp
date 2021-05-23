#include "include/sprite_database.h"

SpriteDatabase::SpriteDatabase() :
	m_sprites({
		/*[Terence	    ]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")), true),
		/*[Red		    ]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")), true),
		/*[Chuck	    ]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")), true),
		/*[JayJakeJim   ]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")), true),
		/*[PigMinion    ]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")), true),
		/*[WoodTriangle ]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("blocks"), 874, 0, 82, 82)),
		/*[WoodSquare   ]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("blocks"), 709, 0, 82, 82)),
		/*[WoodRectangle]*/ Sprite(TextureRegion(AssetManager::getInstance().getSprite("blocks"), 314, 614, 200, 20))
	}) {

}

const Sprite& SpriteDatabase::fromTypeToSprite(EntityType type) const {
	return m_sprites[type];
}

SpriteDatabase& SpriteDatabase::getInstance() {
	static SpriteDatabase database;
	return database;
}
