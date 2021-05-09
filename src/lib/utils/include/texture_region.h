//
// Created by Viktor on 15.1.2021 г..
//

#ifndef TEXTURE_REGION_H
#define TEXTURE_REGION_H


#include "texture.h"

class TextureRegion {
private:
	std::shared_ptr<Texture> texture;
	/** bottom-left corner */
	float u, v;
	/** front-right corner */
	float u2, v2;
	int regionWidth;
	int regionHeight;
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
	TextureRegion** split(int blockWidth, int blockHeight);

	TextureRegion& operator+(const TextureRegion& tR);

	template<typename Archive>
	void serialize(Archive& archive);
};

template <typename Archive>
void TextureRegion::serialize(Archive& archive) {
	archive(texture, u, v, u2, v2);
}


#endif //TEXTURE_REGION_H
