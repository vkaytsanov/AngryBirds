#include "include/screen_manager.h"

#include "../systems/include/render_system.h"
#include "../systems/include/debug_system.h"
#include "../systems/include/animator_system.h"
#include "../systems/include/transform_system.h"
#include "../systems/include/physics_system_2d.h"
#include "../systems/include/bird_system.h"
#include "../systems/include/particle_system.h"
#include "../systems/include/user_interface_system.h"
#include "../systems/include/game_state_system.h"

#include "../components/2d/include/animator.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../components/include/particle_emitter.h"
#include "../components/include/pig.h"
#include "../components/include/obstacle.h"
#include "../data/include/config_development.h"


ScreenManager::ScreenManager() : m_screens({}),
                                 m_menuScreen(&m_gameStateManager),
                                 m_playingScreen(&m_gameStateManager),
                                 m_gameWonWindow(&m_gameStateManager),
                                 m_gameLostWindow(&m_gameStateManager) {

	m_entityX.systems.add<TransformSystem>();
	m_entityX.systems.add<PhysicsSystem2D>();
	m_entityX.systems.add<BirdSystem>();
	m_entityX.systems.add<AnimatorSystem>();
	m_entityX.systems.add<ParticleSystem>();
#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
	m_entityX.systems.add<RenderSystem>(m_entityX.systems.system<PhysicsSystem2D>()->getDebugDraw());
#else
	m_entityX.systems.add<RenderSystem>();
#endif
	m_entityX.systems.add<UserInterfaceSystem>();
	m_entityX.systems.add<GameStateSystem>(&m_gameStateManager);
	//m_entityX.systems.add<DebugSystem>();

	// TODO fix this in more convenient way
	// initializing component pools for all the components
	auto entity = m_entityX.entities.create();
	entity.addComponent<Transform>();
	entity.addComponent<Sprite>();
	entity.addComponent<RigidBody2D>();
	entity.addComponent<Bird>();
	entity.addComponent<Pig>();
	entity.addComponent<Obstacle>();
	entity.addComponent<ParticleEmitter>();
	entity.addComponent<Animator>();
	entity.addComponent<Button>();
	entity.destroy();

	m_screens[Menu] = &m_menuScreen;
	m_screens[Playing] = &m_playingScreen;
	m_screens[GameLost] = &m_gameLostWindow;
	m_screens[GameWon] = &m_gameWonWindow;

	m_entityX.systems.configure();

#if !defined(USE_EDITOR)
	m_screens[m_gameStateManager.getCurrentState()]->start(&m_entityX);
#endif
}

void ScreenManager::update() {
	if (m_gameStateManager.hasChanged()) {
		m_screens[m_gameStateManager.getCurrentState()]->start(&m_entityX);
	}
	m_gameStateManager.update();

	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
}
