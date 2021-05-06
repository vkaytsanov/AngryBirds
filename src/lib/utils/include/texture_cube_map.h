//
// Created by Viktor on 24.2.2021 г..
//

#ifndef TEXTURE_CUBE_MAP_H
#define TEXTURE_CUBE_MAP_H

#include "GL/glew.h"
#include <string>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

class TextureCubeMap {
private:
	unsigned int textureBuffer;
	SDL_Surface* surface;
	GLenum textureFormat;
	int width;
	int height;
public:
	explicit TextureCubeMap(std::vector<std::string>& paths);
	TextureCubeMap() = default;
	~TextureCubeMap();
	void performChecks();
	unsigned int getBuffer();
	int getWidth() const;
	int getHeight() const;
};



#endif //TEXTURE_CUBE_MAP_H
