//
// Created by Viktor on 24.2.2021 г..
//

#include "include/texture_cube_map.h"
#include "../include/lib.h"

TextureCubeMap::TextureCubeMap(std::vector<std::string>& paths) {
	glGenTextures(1, &textureBuffer);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureBuffer);

	if(paths.size() == 2){
		surface = IMG_Load(paths[0].c_str());
		performChecks();
		for(int i = 0; i < 6; i++) {
			if(i == 2) continue;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			             0,
			             textureFormat,
			             surface->w,
			             surface->h,
			             0,
			             textureFormat,
			             GL_UNSIGNED_BYTE,
			             surface->pixels);
		}
		SDL_FreeSurface(surface);

		surface = IMG_Load(paths[1].c_str());
		performChecks();
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2,
		             0,
		             textureFormat,
		             surface->w,
		             surface->h,
		             0,
		             textureFormat,
		             GL_UNSIGNED_BYTE,
		             surface->pixels);
		SDL_FreeSurface(surface);
	}
	else if(paths.size() == 6){
		for (int i = 0; i < paths.size(); i++) {
			surface = IMG_Load(paths[i].c_str());
			performChecks();

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			             0,
			             textureFormat,
			             surface->w,
			             surface->h,
			             0,
			             textureFormat,
			             GL_UNSIGNED_BYTE,
			             surface->pixels);

			SDL_FreeSurface(surface);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


}

TextureCubeMap::~TextureCubeMap() {
	glDeleteBuffers(1, &textureBuffer);
}

void TextureCubeMap::performChecks() {
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
	int colorCount = surface->format->BytesPerPixel;
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

unsigned int TextureCubeMap::getBuffer() {
	return textureBuffer;
}

int TextureCubeMap::getWidth() const {
	return width;
}

int TextureCubeMap::getHeight() const {
	return height;
}
