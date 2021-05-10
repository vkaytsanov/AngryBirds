#pragma once
#include "entityx/quick.h"
#include "utils/openGL/include/frame_buffer.h"

class Editor {
private:
	entityx::EntityX m_prefabs;
	entityx::Entity* m_selectedEntity = nullptr;
public:
	FrameBuffer m_fbo;
	void update(float dt);
	void renderImGui();
	void showDockSpace(bool* open);
};
