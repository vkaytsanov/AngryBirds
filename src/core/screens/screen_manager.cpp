#include "include/screen_manager.h"

#include "../systems/include/render_system.h"
#include "../systems/include/debug_system.h"
#include "../systems/include/animator_system.h"
#include "../systems/include/transform_system.h"
#include "../systems/include/physics_system_2d.h"
#include "../systems/include/bird_system.h"
#include "../systems/include/particle_system.h"
#include "../systems/include/user_interface_system.h"

#include "../components/2d/include/animator.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../components/include/particle_emitter.h"
#include "../components/include/pig.h"

ScreenManager::ScreenManager() : m_menuScreen(&m_gameStateManager),
                                 m_playingScreen(&m_gameStateManager) {

	m_entityX.systems.add<TransformSystem>();
	m_entityX.systems.add<PhysicsSystem2D>();
	m_entityX.systems.add<BirdSystem>();
	m_entityX.systems.add<AnimatorSystem>();
	m_entityX.systems.add<ParticleSystem>();
	m_entityX.systems.add<RenderSystem>(m_entityX.systems.system<PhysicsSystem2D>()->getDebugDraw());
	m_entityX.systems.add<UserInterfaceSystem>();
	m_entityX.systems.add<DebugSystem>();

	// TODO fix this in more convenient way
	// initializing component pools for all the components
	auto entity = m_entityX.entities.create();
	entity.addComponent<Transform>();
	entity.addComponent<Sprite>();
	entity.addComponent<RigidBody2D>();
	entity.addComponent<Bird>();
	entity.addComponent<Pig>();
	entity.addComponent<ParticleEmitter>();
	entity.addComponent<Animator>();
	entity.addComponent<Button>();
	entity.destroy();

	m_screens[0] = &m_menuScreen;
	m_screens[1] = &m_playingScreen;

	m_entityX.systems.configure();

	m_gameStateManager.changeState(Menu);
	m_screens[m_gameStateManager.getCurrentState()]->start(&m_entityX);
}

void ScreenManager::update() {
	if(m_gameStateManager.hasChanged()) {
		m_screens[m_gameStateManager.getCurrentState()]->start(&m_entityX);
	}
	m_gameStateManager.update();
	
	m_entityX.systems.updateAll(Lib::graphics->getDeltaTime());
}
