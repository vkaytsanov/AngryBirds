
#ifndef MINECRAFT
#define MINECRAFT


#include "../../lib/include/listener.h"
#include "game_state_manager.h"
#include "../../lib/entityx/entityx.h"
#include "../scene_editor/include/editor.h"

#define USE_EDITOR

class AngryBirds : public Listener {
public:
	entityx::EntityX m_entityX;
#ifdef USE_EDITOR
	std::unique_ptr<Editor> m_pEditor;
#endif
	GameStateManager m_gameStateManager;
	AngryBirds();
	~AngryBirds() override;
	// Inherited via Listener
	void create() override;
	void render() override;
	void renderImGui() override;
	void pause() override;
	void resume() override;
	void resize(const int width, const int height) override;

	void deserialize();
	void serialize();
};

#endif