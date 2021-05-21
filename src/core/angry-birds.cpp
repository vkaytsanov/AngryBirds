//
// Created by Viktor on 23.12.2020 г..
//

#include "include/angry-birds.h"
#include "../lib/include/lib.h"
#include "components/2d/include/animator.h"
#include "components/2d/include/rigid_body_2d.h"
#include "components/2d/include/sprite.h"
#include "components/include/particle_emitter.h"
#include "systems/include/render_system.h"
#include "systems/include/debug_system.h"

#include "data/include/asset_manager.h"
#include "data/include/box2d_database.h"
#include "systems/include/animator_system.h"
#include "systems/include/transform_system.h"
#include "systems/include/physics_system_2d.h"
#include "utils/include/animation.h"

#include "data/include/animators_database.h"
#include "systems/include/bird_system.h"
#include "systems/include/particle_system.h"

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
#if defined(_DEBUG)
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
#endif
	AssetManager::getInstance();
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_entityX.systems.add<TransformSystem>();
	m_entityX.systems.add<PhysicsSystem2D>();
	m_entityX.systems.add<BirdSystem>();
	m_entityX.systems.add<AnimatorSystem>();
	m_entityX.systems.add<ParticleSystem>();
	m_entityX.systems.add<RenderSystem>(m_entityX.systems.system<PhysicsSystem2D>()->getDebugDraw());
	m_entityX.systems.add<DebugSystem>();
	

#if defined(USE_EDITOR)
	// initializing component pools for this entity manager
	auto entity = m_entityX.entities.create();
	entity.addComponent<Transform>();
	entity.addComponent<Sprite>();
	entity.destroy();
	m_pEditor = std::make_unique<Editor>(&m_entityX);
	m_pEditor->update(Lib::graphics->getDeltaTime());
#endif
	{
		// auto background = m_entityX.entities.create();
		// auto ts = background.addComponent<Transform>();
		// ts->scale = Vector3f(25, 20, 1);
		// background.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("background")));
	}
	// {
	// entityx::Entity ent = m_entityX.entities.create();
	// 	ent.addComponent<Transform>();
	// 	ent.addComponent<RigidBody>();
	// }
	// {
	// entityx::Entity ent = m_entityX.entities.create();
	// ent.addComponent<Transform>(Vector3f(5, 3, 2));
	// }

	// 	auto boxObstacleWood = m_entityX.entities.create();
	// 	boxObstacleWood.addComponent<Transform>();
	// 	boxObstacleWood.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("blocks"), 709, 0, 82,
	// 	                                                   82));
	// 	boxObstacleWood.addComponent<RigidBody2D>(boxBody, boxDef);

	// 	auto triangleObstacleWood = m_entityX.entities.create();
	// 	triangleObstacleWood.addComponent<Transform>();
	// 	triangleObstacleWood.addComponent<Sprite>(
	// 		TextureRegion(AssetManager::getInstance().getSprite("blocks"), 874, 0, 82, 82));
	// 	triangleObstacleWood.addComponent<RigidBody2D>(triangleBody, triangleDef);


	// auto plankObstacleWood = m_entityX.entities.create();
	// plankObstacleWood.addComponent<Transform>()->scale = Vector3f(2, 0.4f, 0);
	// plankObstacleWood.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("blocks"), 314, 614, 200,
	//                                                      20));
	// plankObstacleWood.addComponent<RigidBody2D>(Box2dDatabase::getInstance().m_plankBody);

	auto normalPig = m_entityX.entities.create();
	normalPig.addComponent<Transform>()->position = Vector3f(0, -17, 0);
	normalPig.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")), true);
	normalPig.addComponent<Animator>(AnimatorsDatabase::getInstance().m_pigAnimator);
	normalPig.addComponent<RigidBody2D>(Box2dDatabase::getInstance().m_terenceBody);
	
	// auto normalPig2 = m_entityX.entities.create();
	// normalPig2.addComponent<Transform>(Vector3f(0.5, 10, 0));
	// normalPig2.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("pigs"), 679, 790, 99, 97));
	// normalPig2.addComponent<RigidBody2D>(m_bodyDef, m_fixtureDef);
	
	{
		auto ground = m_entityX.entities.create();
		auto ts = ground.addComponent<Transform>(Vector3f(0, -50, 0));
		ts->scale = Vector3f(10, 1.4f, 1);
		TextureRegion groundTR = TextureRegion(AssetManager::getInstance().getSprite("ground"));
		groundTR.setTiling(10, 1);
		ground.addComponent<Sprite>(std::move(groundTR));
		ground.addComponent<RigidBody2D>(Box2dDatabase::getInstance().m_groundBody);
	}
	{
		// auto entity = m_entityX.entities.create();
		// entity.addComponent<Transform>();
		// entity.addComponent<Sprite>();
		//
		// entity.addComponent<Animator>();
	}
	
	auto backSling = m_entityX.entities.create();
	auto ts = backSling.addComponent<Transform>();
	ts->position = Vector3f(-60, -16, 0);
	backSling.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 563, 0, 40, 200));
	
	m_entityX.systems.system<BirdSystem>()->addBird(m_entityX.entities, Red);
	m_entityX.systems.system<BirdSystem>()->addBird(m_entityX.entities, Terence);

	auto frontSling = m_entityX.entities.create();
	auto ts2 = frontSling.addComponent<Transform>();
	ts2->position = Vector3f(-63.7f, -10.4f, 0);
	
	frontSling.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 733, 160, 43, 125));
	
	m_entityX.systems.configure();
	m_entityX.systems.system<PhysicsSystem2D>()->initializeBodies(m_entityX.entities);
	
}

void AngryBirds::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

#if defined(USE_EDITOR)
	m_pEditor->update(Lib::graphics->getDeltaTime());
#else
	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
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
	m_entityX.systems.system<RenderSystem>()->onResize(width, height);
}
