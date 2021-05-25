//
// Created by Viktor on 23.12.2020 г..
//

#include "include/angry-birds.h"
#include "../lib/include/lib.h"
#include "components/2d/include/sprite.h"
#include "data/include/asset_manager.h"
#include "data/include/audio_database.h"
#include "utils/include/texture_region.h"

#include "systems/include/render_system.h"



void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s m_type = 0x%x, severity = 0x%x, message = %s\n",
	        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	        type, severity, message);
}

AngryBirds::~AngryBirds() {
	// since it is static and we have allocated SDL2_Mixer memory that
	// need to be released before calling #Mix_Quit
	AudioDatabase::getInstance().free();
}

void AngryBirds::create() {
#if defined(_DEBUG) && !defined(USE_EDITOR)
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
#endif
	
	AssetManager::getInstance();
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_pScreenManager = std::make_unique<ScreenManager>();

#if defined(USE_EDITOR)
	auto ground = m_pScreenManager->m_entityX.entities.create();
	auto ts = ground.addComponent<Transform>(Vector3f(0, -50, 0));
	ts->scale = Vector3f(10, 1.4f, 1);
	TextureRegion groundTR = TextureRegion(AssetManager::getInstance().getSprite("ground"));
	groundTR.setTiling(10, 1);
	ground.addComponent<Sprite>(std::move(groundTR));

	m_pEditor = std::make_unique<Editor>(&m_pScreenManager->m_entityX);
	m_pEditor->update(Lib::graphics->getDeltaTime());
#endif
}

void AngryBirds::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

#if defined(USE_EDITOR)
	m_pEditor->update(Lib::graphics->getDeltaTime());
#else
	m_pScreenManager->update();
#endif
	
}

void AngryBirds::renderImGui() {
#if defined(USE_EDITOR)
	m_pEditor->renderImGui();
#endif
}

void AngryBirds::pause() {

}

void AngryBirds::resume() {

}

void AngryBirds::resize(const int width, const int height) {
	m_pScreenManager->m_entityX.systems.system<RenderSystem>()->onResize(width, height);
}
