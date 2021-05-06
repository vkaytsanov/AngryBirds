
#ifndef MINECRAFT
#define MINECRAFT


#include "../../lib/include/listener.h"
#include "game_state_manager.h"
#include "../../lib/entityx/entityx.h"


class AngryBirds : public Listener {
public:
	entityx::EntityX m_entityX;
	GameStateManager m_gameStateManager;


	AngryBirds() = default;
	~AngryBirds() override;
	// Inherited via Listener
	void create() override;
	void render() override;
	void renderImGui() override;
	void pause() override;
	void resume() override;
	void resize(const int width, const int height) override;
};

#endif