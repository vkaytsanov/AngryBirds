//
// Created by Viktor on 8.1.2021 г..
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>

enum TextureFilter {
	Nearest = GL_NEAREST,
	Linear = GL_LINEAR,
	MipMap = GL_MIPMAP,
	MipMapNearestNearest = GL_NEAREST_MIPMAP_NEAREST,
	MipMapLinearNearest = GL_LINEAR_MIPMAP_NEAREST,
	MipMapNearestLinear = GL_NEAREST_MIPMAP_LINEAR,
	MipMapLinearLinear = GL_LINEAR_MIPMAP_LINEAR,
};

enum TextureWrap {
	Repeat = GL_REPEAT,
	RepeatMirrored = GL_MIRRORED_REPEAT,
	ClampToEdge = GL_CLAMP_TO_EDGE,
};

class Texture {
private:
	unsigned int textureBuffer;
	SDL_Surface* surface;
	GLenum textureFormat;
	int colorCount;
	int width;
	int height;
public:
	explicit Texture(std::string path);
	Texture() = default;
	~Texture();
	void performChecks();
	unsigned int getBuffer() const;
	int getWidth() const;
	int getHeight() const;
};


#endif //TEXTURE_H
