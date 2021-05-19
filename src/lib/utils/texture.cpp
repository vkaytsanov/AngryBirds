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
	m_surface = IMG_Load((m_dir + m_name).c_str());

	performChecks();

	glGenTextures(1, &m_textureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, flags);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, flags);
	
	glTexImage2D(GL_TEXTURE_2D,
	             0,
	             m_textureFormat,
	             m_surface->w,
	             m_surface->h,
	             0,
	             m_textureFormat,
	             GL_UNSIGNED_BYTE,
	             m_surface->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	SDL_FreeSurface(m_surface);
	m_surface = nullptr;
}

void Texture::performChecks() {
	if (m_surface == nullptr) {
		Lib::app->error("TextureError", SDL_GetError());
		exit(-1);
	}
	if ((m_surface->w & (m_surface->w - 1)) != 0) {
		Lib::app->error("TextureError", "BMP's width is not a power of 2");
	}
	if ((m_surface->h & (m_surface->h - 1)) != 0) {
		Lib::app->error("TextureError", "BMP's height is not a power of 2");
	}
	m_colorCount = m_surface->format->BytesPerPixel;
	if (m_colorCount == 4) {
		// contains alpha channel
		m_textureFormat = m_surface->format->Rmask == 0x000000ff ? GL_RGBA : GL_BGRA;
	}
	else if (m_colorCount == 3) {
		m_textureFormat = m_surface->format->Rmask == 0x000000ff ? GL_RGB : GL_BGR;
	}
	else {
		Lib::app->error("TextureError", "Colors arent right");
		exit(-1);
	}

	m_width = m_surface->w;
	m_height = m_surface->h;

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
