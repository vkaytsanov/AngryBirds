#include "include/editor_asset_manager.h"
#include "include/lib.h"

EditorAssetManager::EditorAssetManager() {
	std::string iconNames[] = {
		"bin.png"
	};

	int c = 0;
	for (const std::string& path : iconNames) {
		m_icons[stripName(path)] = std::make_shared<Texture>(ICONS_LOCATION, path);
		c++;
	}

	std::cout << c << " sprites loaded\n";
}

std::shared_ptr<Texture> EditorAssetManager::getIcon(const std::string& name) {
#if _DEBUG
	if (m_icons.find(name) == m_icons.end()) {
		std::cout << "Sprite " + name + " doesn't exists";
	}
#endif
	return m_icons.at(name);
}

std::string EditorAssetManager::stripName(const std::string& name) {
	return name.substr(0, name.length() - 4);
}
