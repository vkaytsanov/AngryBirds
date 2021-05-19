//
// Created by Viktor on 18.12.2020 г..
//

#include <iostream>
#include "include/asset_manager.h"


AssetManager::AssetManager() {
	const std::string spritePaths[] = {
		"blocks.png",
		"birds.png",
		"pigs.png",
		"background.png",
		"ground.png",
		"all-in-one.png"
	};
	int c = 0;
	for (const std::string& path : spritePaths) {
		m_spriteSheets[stripName(path)] = std::make_shared<Texture>(ASSETS_LOCATION, path);
		c++;
	}
	

	std::cout << c << " sprites loaded\n";

}

std::shared_ptr<Texture> AssetManager::getSprite(const std::string name) const {
#if _DEBUG 
	if (m_spriteSheets.find(name) == m_spriteSheets.end()) {
		std::cout << "Sprite " + name + " doesn't exists";
	}
#endif
	return m_spriteSheets.at(name);
}

AssetManager::~AssetManager() {
}

std::string AssetManager::stripName(const std::string& name) {
	return name.substr(0, name.length() - 4);
}

AssetManager& AssetManager::getInstance() {
	//std::cout << "Creating instance\n";
	static AssetManager instance;
	return instance;
}


