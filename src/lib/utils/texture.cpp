//
// Created by Viktor on 8.1.2021 г..
//

#include "include/texture.h"
#include "../include/lib.h"


Texture::Texture(std::string path) {
	surface = IMG_Load(path.c_str());

	performChecks();

	glGenTextures(1, &textureBuffer);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
	             0,
	             textureFormat,
	             surface->w,
	             surface->h,
	             0,
	             textureFormat,
	             GL_UNSIGNED_BYTE,
	             surface->pixels);
	SDL_FreeSurface(surface);
	surface = nullptr;
}

Texture::~Texture() {
	
	glDeleteBuffers(1, &textureBuffer);
}

void Texture::performChecks() {
	if (surface == nullptr) {
		Lib::app->error("TextureError", SDL_GetError());
		exit(-1);
	}
	if ((surface->w & (surface->w - 1)) != 0) {
		Lib::app->error("TextureError", "BMP's width is not a power of 2");
	}
	if ((surface->h & (surface->h - 1)) != 0) {
		Lib::app->error("TextureError", "BMP's height is not a power of 2");
	}
	colorCount = surface->format->BytesPerPixel;
	if (colorCount == 4) {
		// contains alpha channel
		textureFormat = surface->format->Rmask == 0x000000ff ? GL_RGBA : GL_BGRA;
	}
	else if (colorCount == 3) {
		textureFormat = surface->format->Rmask == 0x000000ff ? GL_RGB : GL_BGR;
	}
	else {
		Lib::app->error("TextureError", "Colors arent right");
		exit(-1);
	}

	width = surface->w;
	height = surface->h;

}

unsigned int Texture::getBuffer() const{
	return textureBuffer;
}

int Texture::getWidth() const {
	return width;
}

int Texture::getHeight() const {
	return height;
}



