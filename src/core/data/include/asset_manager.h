//
// Created by Viktor on 18.12.2020 г..
//

#ifndef MOD_ASSETS_H
#define MOD_ASSETS_H

#include <unordered_map>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include "../../../lib/utils/include/texture.h"


// TODO Don't know how to use project path
const std::string ASSETS_LOCATION = __FILE__ "/../../../../assets/sprites/";

class AssetManager {
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_spriteSheets;
	static std::string stripName(const std::string& name);
public:
	AssetManager();
	~AssetManager();
	std::shared_ptr<Texture> getSprite(std::string name) const;
	static AssetManager& getInstance();
};


#endif //MOD_ASSETS_H
