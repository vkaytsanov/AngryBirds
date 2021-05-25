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

	TextureRegion groundTR = TextureRegion(AssetManager::getInstance().getSprite("ground"));
	groundTR.setTiling(10, 1);
	m_groundSprite = groundTR;

	m_backgroundSprite = Sprite(TextureRegion(AssetManager::getInstance().getSprite("background")));
	m_backSlingshotSprite = Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 563, 0, 40, 200));
	m_frontSlingshotSprite = Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 733, 160, 43, 125));
}

SpriteDatabase::~SpriteDatabase() {
	for(unsigned i = 0; i < m_sprites.size(); i++) {
		m_sprites[i].getVao()->free();
	}

	m_groundSprite.getVao()->free();
	m_backSlingshotSprite.getVao()->free();
	m_frontSlingshotSprite.getVao()->free();
}

const Sprite& SpriteDatabase::fromTypeToSprite(EntityType type) const {
	return m_sprites[type];
}


const Sprite& SpriteDatabase::getBackground() {
	return m_backgroundSprite;
}

const Sprite& SpriteDatabase::getBackSlingshot() {
	return m_backSlingshotSprite;
}

const Sprite& SpriteDatabase::getFrontSlingshot() {
	return m_frontSlingshotSprite;
}

const Sprite& SpriteDatabase::getGround() {
	return m_groundSprite;
}

SpriteDatabase& SpriteDatabase::getInstance() {
	static SpriteDatabase database;
	return database;
}
