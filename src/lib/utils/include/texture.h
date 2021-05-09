//
// Created by Viktor on 8.1.2021 г..
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include "cereal/types/string.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>


class Texture {
private:
	unsigned int m_textureBuffer;
	SDL_Surface* m_surface;
	GLenum m_textureFormat;
	int m_colorCount;
	int m_width;
	int m_height;
private:
	void init();
public:
	std::string m_dir;
	std::string m_name;
public:
	explicit Texture(const std::string& dir, const std::string& name);
	Texture() = default;
	~Texture();
	void performChecks();
	unsigned int getBuffer() const;
	int getWidth() const;
	int getHeight() const;

	template <typename Archive>
	void save(Archive& archive) const;

	template <typename Archive>
	void load(Archive& archive);
};

template <typename Archive>
void Texture::save(Archive& archive) const {
	archive(m_dir, m_name);
}

template <typename Archive>
void Texture::load(Archive& archive) {
	archive(m_dir, m_name);
	// init();
}


#endif //TEXTURE_H
