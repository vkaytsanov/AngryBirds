#pragma once
#include "utils/include/texture.h"


class EditorAssetManager {
private:
	const std::string ICONS_LOCATION = __FILE__ "/../../assets/";
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_icons;
private:
	std::string stripName(const std::string& name);
public:
	EditorAssetManager();
	std::shared_ptr<Texture> getIcon(const std::string& name);

};
