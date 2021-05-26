//
// Created by Viktor on 11.3.2021 г..
//

#include "include/debug_system.h"
#include "../../lib/utils/ui/include/input_listener.h"

DebugSystem::DebugSystem() {

}

void DebugSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	std::string pixelEmulatorPath = "src/assets/fonts/pixel-emulator.ttf";
	m_pFont = TTF_OpenFont((pixelEmulatorPath).c_str(), 20);
	if (!m_pFont) {
		Lib::app->error("LabelStyle", "Can't load font.");
		Lib::app->error("File path given", (pixelEmulatorPath).c_str());
		exit(-1);
	}
	m_pLabelStyle = new LabelStyle(m_pFont, 20);
	m_playerPos.setStyle(m_pLabelStyle);
	m_playerForward.setStyle(m_pLabelStyle);

	m_playerPos.setPosition(0, 0);
	m_playerPos.setSize(200, 100);

	m_playerForward.setPosition(0, 110);
	m_playerForward.setSize(200, 100);
	m_userInterface.addActor(&m_playerPos);
	m_userInterface.addActor(&m_playerForward);
	auto* inputListener = new InputListener();
#if !defined(__EMSCRIPTEN__)
	inputListener->keyDown = [&](int key) -> void {

		if(key == SDLK_TAB){
			if (m_isWireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			m_isWireframe = !m_isWireframe;
		}
	};
#endif
	m_userInterface.addListener(inputListener);
	Lib::input->setProcessor(&m_userInterface);
	m_userInterface.debug = true;
}

void DebugSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	//	m_playerPos.setText(std::to_string(m_transform->position.x) + " " + std::to_string(m_transform->position.y) + std::to_string(m_transform->position.z));
	//	m_playerForward.setText(std::to_string(m_transform->forward.x) + " " + std::to_string(m_transform->forward.y) + std::to_string(m_transform->forward.z));
	//	m_playerForward.updateText();
	//	m_playerPos.updateText();
	//	m_userInterface.act(dt);
	//	m_userInterface.draw();
}

DebugSystem::~DebugSystem() {
	delete m_pLabelStyle;
	TTF_CloseFont(m_pFont);
}
