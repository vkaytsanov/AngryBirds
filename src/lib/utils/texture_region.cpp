//
// Created by Viktor on 15.1.2021 г..
//

#include "include/texture_region.h"
#include "../include/lib.h"
#include <cmath>


TextureRegion::TextureRegion(std::shared_ptr<Texture> texture) : TextureRegion(texture, 0, 0, texture->getWidth(), texture->getHeight()){
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, int width, int height) : TextureRegion(texture, 0, 0, width, height){
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, int x, int y, int width, int height) : texture(texture){
	setRegionXY(x, y, width, height);
}

void TextureRegion::setRegionXY(int x, int y, int width, int height) {
	float invWidth = 1.00f / (float) texture->getWidth();
	float invHeight = 1.00f / (float) texture->getHeight();

	setRegionUV((float) x * invWidth, (float) y * invHeight, (float) (x + width) * invWidth,
	            (float) (y + height) * invHeight);

	regionWidth = width;
	regionHeight = height;
}

void TextureRegion::setRegionUV(float u, float v, float u2, float v2) {

	this->u = u;
	this->v = v;
	this->u2 = u2;
	this->v2 = v2;
}

TextureRegion& TextureRegion::setRegionUV(std::shared_ptr<Texture> texture, float u, float v, float u2, float v2) {
	this->texture = texture;
	this->u = u;
	this->v = v;
	this->u2 = u2;
	this->v2 = v2;

	return *this;
}

void TextureRegion::setTexture(std::shared_ptr<Texture> texture) {
	this->texture = texture;
}

std::shared_ptr<Texture> TextureRegion::getTexture() const {
	return texture;
}

float TextureRegion::getU() const {
	return u;
}

float TextureRegion::getV() const {
	return v;
}

float TextureRegion::getU2() const {
	return u2;
}

float TextureRegion::getV2() const {
	return v2;
}

TextureRegion** TextureRegion::split(int blockWidth, int blockHeight) {
	int rows = regionHeight / blockHeight;
	int cols = regionWidth / blockWidth;

	TextureRegion** blocks = new TextureRegion* [rows];
	for (int i = 0; i < rows; i++) {
		blocks[i] = new TextureRegion[cols];
	}


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			blocks[i][j] = TextureRegion(texture, i * blockWidth, j * blockHeight, blockWidth, blockHeight);
		}
	}
	return blocks;
}

std::array<float, 8> TextureRegion::getPackedUvs() const{
	return {
		u, v2,
		u2, v2,
		u2, v,
		u, v
	};
}


float* TextureRegion::getUVs() {
	return new float[6 * 4 * 2]{
			// front
			u, v2,
			u2, v2,
			u2, v,
			u, v,
			// back
			u2, v2,
			u, v2,
			u, v,
			u2, v,
			// front
			u, v2,
			u2, v2,
			u2, v,
			u, v,
			//bottom
			u, v2,
			u2, v2,
			u2, v,
			u, v,
			//left
			u, v,
			u2, v,
			u2, v2,
			u, v2,
			//right
			u, v2,
			u, v,
			u2, v,
			u2, v2,


	};


}

void TextureRegion::setTiling(int x, int y) {
	m_tilingX = x;
	m_tilingY = y;
}

int TextureRegion::getRegionX() const {
	return (int) std::round(u * (float) texture->getWidth());
}

int TextureRegion::getRegionY() const {
	return (int) std::round(v * (float) texture->getHeight());
}

int TextureRegion::getRegionWidth() const {
	return regionWidth;
}

int TextureRegion::getRegionHeight() const {
	return regionHeight;
}

TextureRegion& TextureRegion::operator+(const TextureRegion& tR) {
	setRegionXY(std::min(getRegionX(), tR.getRegionX()), std::min(getRegionY(), tR.getRegionY()),
	            regionWidth + tR.regionWidth, regionHeight);
	return *this;
}




