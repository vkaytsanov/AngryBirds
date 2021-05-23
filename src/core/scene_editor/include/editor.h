#pragma once
#include "editor_asset_manager.h"
#include "scene_manager.h"
#include "entityx/quick.h"
#include "imgui/imgui.h"
#include "utils/openGL/include/frame_buffer.h"

class Editor {
private:
	bool isDirty = true; // initial render in the fbo
	FrameBuffer m_fbo;

	bool m_saveAsPopUp = false;
	bool m_newScenePopUp = false;
	
	entityx::EntityX* m_pEntityX;
	entityx::EventManager m_eventManager;
	entityx::EntityManager m_prefabs;
	entityx::Entity m_pSelectedEntity;

	EditorAssetManager m_editorAssetManager;
	SceneManager m_sceneManager;
	ImVec2 gameWindowBottomRightPos;
	ImVec2 gameWindowTopLeftPos;
private:
	void loadPrefabs();
	void onSceneChange();
	void addToCurrentScene(const entityx::Entity entity);
	void showDockSpace(bool* open);
	void drawMenuBar();
	void drawHierarchy();
	void drawSceneWindow();
	void drawDetails();
	void drawPrefabsWindow();
	void drawAvailableScenesWindow();
	void drawTransformComponentWidget();
	void drawPopUps();
public:
	Editor(entityx::EntityX* entityX);
	void update(float dt);
	void renderImGui();
	
};
