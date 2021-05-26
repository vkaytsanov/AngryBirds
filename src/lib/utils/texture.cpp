//
// Created by Viktor on 8.1.2021 г..
//

#include "include/texture.h"
#include "../include/lib.h"

Texture::Texture(const std::string& dir, const std::string& name) :
	Texture(dir, name, GL_REPEAT) {

}

Texture::Texture(const std::string& dir, const std::string& name, GLint wrapFlags) :
	m_dir(dir),
	m_name(name) {

	init(wrapFlags);
}

Texture::~Texture() {
	glDeleteBuffers(1, &m_textureBuffer);
}

void Texture::init(GLint flags) {
	SDL_Surface* surface = IMG_Load((m_dir + m_name).c_str());

	performChecks(surface);

	glGenTextures(1, &m_textureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, flags);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, flags);

	
	glTexImage2D(GL_TEXTURE_2D,
	             0,
	             m_textureFormat,
	             surface->w,
	             surface->h,
	             0,
	             m_textureFormat,
	             GL_UNSIGNED_BYTE,
	             surface->pixels);

#if !defined(__EMSCRIPTEN__)
	glGenerateMipmap(GL_TEXTURE_2D);
#endif
	glBindTexture(GL_TEXTURE_2D, 0);
	
	SDL_FreeSurface(surface);
}

void Texture::performChecks(SDL_Surface* surface) {
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
	m_colorCount = surface->format->BytesPerPixel;
#if !defined(__EMSCRIPTEN__)
	if (m_colorCount == 4) {
		// contains alpha channel
		m_textureFormat = surface->format->Rmask == 0x000000ff ? GL_RGBA : GL_BGRA;
	}
	else if (m_colorCount == 3) {
		m_textureFormat = surface->format->Rmask == 0x000000ff ? GL_RGB : GL_BGR;
	}
#else
	if (m_colorCount == 4) {
		// contains alpha channel
		m_textureFormat = GL_RGBA;
	}
	else if (m_colorCount == 3) {
		m_textureFormat = GL_RGB;
	}
#endif
	else {
		Lib::app->error("TextureError", "Colors arent right");
		exit(-1);
	}

	m_width = surface->w;
	m_height = surface->h;

}

unsigned int Texture::getBuffer() const {
	return m_textureBuffer;
}

int Texture::getWidth() const {
	return m_width;
}

int Texture::getHeight() const {
	return m_height;
}
