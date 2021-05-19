//
// Created by Viktor on 15.1.2021 г..
//

#ifndef TEXTURE_REGION_H
#define TEXTURE_REGION_H


#include "texture.h"
#include "../../../core/data/include/asset_manager.h"

class TextureRegion {
private:
	std::shared_ptr<Texture> texture;
	/** bottom-left corner */
	float u = 0, v = 0;
	/** front-right corner */
	float u2 = 1, v2 = 1;
	int regionWidth = 0;
	int regionHeight = 0;
public:
	int m_tilingX = 1;
	int m_tilingY = 1;
public:
	TextureRegion() = default;
	explicit TextureRegion(std::shared_ptr<Texture> texture);
	TextureRegion(std::shared_ptr<Texture> texture, int width, int height);
	TextureRegion(std::shared_ptr<Texture> texture, int x, int y, int width, int height);
	void setRegionXY(int x, int y, int width, int height);
	void setRegionUV(float u, float v, float u2, float v2);
	TextureRegion& setRegionUV(std::shared_ptr<Texture> texture, float u, float v, float u2, float v2);
	void setTexture(std::shared_ptr<Texture> texture);
	std::shared_ptr<Texture> getTexture() const;
	float getU() const;
	float getV() const;
	float getU2() const;
	float getV2() const;
	
	int getRegionX() const;
	int getRegionY() const;
	int getRegionWidth() const;
	int getRegionHeight() const;
	float* getUVs();
	void setTiling(int x, int y);
	TextureRegion** split(int blockWidth, int blockHeight);

	TextureRegion& operator+(const TextureRegion& tR);

	template<typename Archive>
	void save(Archive& archive) const;

	template<typename Archive>
	void load(Archive& archive);
};

template <typename Archive>
void TextureRegion::save(Archive& archive) const {
	archive(texture, u, v, u2, v2);
}

template <typename Archive>
void TextureRegion::load(Archive& archive) {
	archive(texture, u, v, u2, v2);
	// we get only the directory and name of the texture and now we are just getting the real
	// sprite from the asset manager, instead of creating new one
	texture = AssetManager::getInstance().getSprite(texture->m_name.substr(0, texture->m_name.length() - 4));
}


#endif //TEXTURE_REGION_H
