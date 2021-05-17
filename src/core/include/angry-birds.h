
#ifndef MINECRAFT
#define MINECRAFT


#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>

#include "../../lib/include/listener.h"
#include "game_state_manager.h"
#include "../../lib/entityx/entityx.h"
#include "../scene_editor/include/editor.h"
#include "utils/box2d/b2draw/DebugDraw.h"

#ifdef _DEBUG
// #define USE_EDITOR
#endif

class AngryBirds : public Listener {
public:
	entityx::EntityX m_entityX;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_fixtureDef;
#ifdef USE_EDITOR
	std::unique_ptr<Editor> m_pEditor;
#endif
	GameStateManager m_gameStateManager;
	// Inherited via Listener
	void create() override;
	void render() override;
	void renderImGui() override;
	void pause() override;
	void resume() override;
	void resize(const int width, const int height) override;
	
};

#endif