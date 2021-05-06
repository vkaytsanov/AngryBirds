//
// Created by Viktor on 15.1.2021 г..
//

#ifndef TEXTURE_REGION_H
#define TEXTURE_REGION_H


#include "texture.h"

class TextureRegion {
private:
	const Texture* texture;
	/** bottom-left corner */
	float u, v;
	/** front-right corner */
	float u2, v2;
	int regionWidth;
	int regionHeight;
public:
	TextureRegion() = default;
	explicit TextureRegion(const Texture* texture);
	TextureRegion(Texture* texture, int width, int height);
	TextureRegion(const Texture* texture, int x, int y, int width, int height);
	void setRegionXY(int x, int y, int width, int height);
	void setRegionUV(float u, float v, float u2, float v2);
	const Texture* getTexture() const;
	float getU() const;
	float getV() const;
	float getU2() const;
	float getV2() const;
	int getRegionX() const;
	int getRegionY() const;
	float* getUVs();
	TextureRegion** split(int blockWidth, int blockHeight);

	TextureRegion& operator+(const TextureRegion& tR);


};


#endif //TEXTURE_REGION_H
