//
// Created by Viktor on 23.12.2020 г..
//

#include "include/angry-birds.h"
#include "../lib/include/lib.h"
#include "components/include/sprite.h"
#include "systems/include/render_system.h"
#include "systems/include/debug_system.h"

#include "data/include/asset_manager.h"
#include "systems/include/transform_system.h"
#include "systems/include/physics_system.h"





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

void AngryBirds::create() {
	//
	// glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	// glEnable(GL_DEBUG_OUTPUT);
	// glDebugMessageCallback(MessageCallback, 0);
	AssetManager::getInstance();
	// glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_LEQUAL);
	// glDisable(GL_CULL_FACE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_entityX.systems.add<TransformSystem>();
	m_entityX.systems.add<PhysicsSystem>();
	m_entityX.systems.add<RenderSystem>();
	m_entityX.systems.add<DebugSystem>();
	m_entityX.systems.configure();
	
#ifdef USE_EDITOR
	// initializing component pools for this entity manager
	auto entity = m_entityX.entities.create();
	entity.addComponent<Transform>();
	entity.addComponent<Sprite>();
	entity.destroy();
	m_pEditor = std::make_unique<Editor>(&m_entityX);
	m_pEditor->update(Lib::graphics->getDeltaTime());
#endif
	

	// {
	// entityx::Entity ent = m_entityX.entities.create();
	// 	ent.addComponent<Transform>();
	// 	ent.addComponent<RigidBody>();
	// }
	// {
	// entityx::Entity ent = m_entityX.entities.create();
	// ent.addComponent<Transform>(Vector3f(5, 3, 2));
	// }

	// auto normalPig = m_entityX.entities.create();
	// normalPig.addComponent<Transform>();
	// normalPig.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("pigs"), 679, 790, 99, 97));

	// deserialize();

}

void AngryBirds::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

#ifdef USE_EDITOR
	m_pEditor->update(Lib::graphics->getDeltaTime());
#else
	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
#endif
}

void AngryBirds::renderImGui() {
#ifdef USE_EDITOR
	m_pEditor->renderImGui();
#endif
}

void AngryBirds::pause() {

}

void AngryBirds::resume() {

}

void AngryBirds::resize(const int width, const int height) {
	//m_pGraphicsSystem->resizeViewport(width, height);
}

AngryBirds::AngryBirds() {
}

AngryBirds::~AngryBirds() {
	// serialize();
}
