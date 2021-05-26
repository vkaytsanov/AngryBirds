//
// Created by Viktor on 24.2.2021 г..
//

#ifndef TEXTURE_CUBE_MAP_H
#define TEXTURE_CUBE_MAP_H


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GLES3/gl3.h>
#else
#include "GL/glew.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <string>
#include <vector>



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
