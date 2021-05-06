//
// Created by Viktor on 18.12.2020 г..
//

#include <stdexcept>
#include <iostream>
#include "include/asset_manager.h"


AssetManager::AssetManager() {
	std::cout << "Creating assetmanager\n";
	const std::string spritePaths[] = {
			"spriteSheet.png",
	};

	int c = 0;
	for (const std::string& path : spritePaths) {
		m_mappedSprites[stripName(path)] = new Texture(ASSETS_LOCATION + path);
		c++;
	}

	std::cout << c << " sprites loaded\n";

}

const Texture* AssetManager::getSprite(const std::string name) const {
	if (m_mappedSprites.find(name) == m_mappedSprites.end()) {
		std::cout << "Sprite " + name + " doesn't exists";
	}
	return m_mappedSprites.at(name);
}

AssetManager::~AssetManager() {
	for (const auto& textureData : m_mappedCubeTextures) {
		delete[] textureData.uvs;
	}

	for (const auto& it : m_mappedSprites) {
		delete it.second;
	}
}

std::string AssetManager::stripName(const std::string& name) {
	return name.substr(0, name.length() - 4);
}

AssetManager& AssetManager::getInstance() {
	//std::cout << "Creating instance\n";
	static AssetManager instance;
	return instance;
}


