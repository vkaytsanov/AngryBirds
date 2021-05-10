#pragma once
#include "entityx/quick.h"
#include "imgui/imgui.h"
#include "utils/openGL/include/frame_buffer.h"

class Editor {
private:
	entityx::EventManager m_eventManager;
	entityx::EntityManager m_prefabs;
	entityx::Entity* m_pSelectedEntity = nullptr;

	ImVec2 gameWindowBottomRightPos;
	ImVec2 gameWindowTopLeftPos;
	void loadPrefabs();
	void addToCurrentScene(entityx::EntityX* entityX, const entityx::Entity entity);
public:
	FrameBuffer m_fbo;
public:
	Editor();
	void update(float dt);
	
	void renderImGui(entityx::EntityX* entityX);
	void showDockSpace(bool* open);
	void drawTransformComponentWidget();
};
