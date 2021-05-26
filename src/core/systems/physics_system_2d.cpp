#include "include/physics_system_2d.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/animator.h"
#include "../components/include/transform.h"

#include "../events/the_bird_is_gone.h"
#include "../events/pig_killed.h"
#include "../data/include/audio_database.h"
#include "../data/include/animators_database.h"

#if !defined(__EMSCRIPTEN__)
#include "box2d/b2_contact.h"
#else
#include "box2d-emscripten/Dynamics/Contacts/b2Contact.h"
#endif

struct Obstacle;
struct Bird;
struct Pig;

PhysicsSystem2D::PhysicsSystem2D() : m_world(b2Vec2(0, -9.8f)){
#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
	m_debugDraw.SetAttribLocations(0,1);
	m_debugDraw.SetFlags(0xff);
	m_world.SetDebugDraw(&m_debugDraw);
#endif
}


void PhysicsSystem2D::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
}

void PhysicsSystem2D::configure(entityx::EventManager& events) {
}

void PhysicsSystem2D::initializeBodies(entityx::EntityManager& entities) {
	for (entityx::Entity entity : entities.entities_with_components<RigidBody2D>()) {
		auto transform = entity.getComponent<Transform>();
		entityx::ComponentHandle<RigidBody2D> ch = entity.getComponent<RigidBody2D>();
		ch->bodyInfo.bodyDef.position = b2Vec2(transform->position.x, transform->position.y);
		ch->bodyInfo.bodyDef.angle = transform->eulerAngles.z * MathUtils::DEG2RAD;

		ch->body = m_world.CreateBody(&ch->bodyInfo.bodyDef);
		ch->body->CreateFixture(&ch->bodyInfo.fixtureDef);
	}
}

void PhysicsSystem2D::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events,
                                entityx::TimeDelta dt) {
	static const int32_t velocityIterations = 5;
	static const int32_t positionIterations = 3;
	static const float fixedDeltaTime = 0.016f;
	if (dt == 0.0f) return;

	m_world.Step(fixedDeltaTime, velocityIterations, positionIterations);

	for (auto entity : entities.entities_with_components<RigidBody2D>()) {
		entityx::ComponentHandle<RigidBody2D> rb = entity.getComponent<RigidBody2D>();
		// check if has collisions
		if (rb->body->GetContactList()) {
			// we don't have access to the force vector,
			// so we are going to use the velocity vector for checking collisions
			const b2Vec2 velocity = rb->body->GetLinearVelocity();
			// if a pig has velocity, aka moving -> destroy it
			if (entity.has_component<Pig>()) {
				if (std::abs(velocity.x) > 8 || std::abs(velocity.y) > 8) {
					if (!AudioDatabase::getInstance().isPlaying(SOUND_PIG_DESTROYED)) {
						AudioDatabase::getInstance().play(SOUND_PIG_DESTROYED);
					}
					entity.getComponent<Animator>()->currentAnimation = PigDisappearing;
					events.post<PigKilledEvent>();
					break;
				}
				else if (std::abs(velocity.x) > 2 || std::abs(velocity.y) > 2) {
					// change to damaged
					entity.getComponent<Animator>()->currentAnimation = PigColliding;
				}
			}
			else if (entity.has_component<Bird>()) {
				// if a bird has almost no velocity, we destroy it
				if (std::abs(velocity.x) < 1 || std::abs(velocity.y) < 1) {
					// submit event for the particle system
					events.post<TheBirdIsGone>(
						TheBirdIsGone(entity.getComponent<Bird>()->type, rb->body->GetPosition()));
					// play death sound
					if (!AudioDatabase::getInstance().isPlaying(SOUND_BIRD_YELL)) {
						AudioDatabase::getInstance().play(SOUND_BIRD_YELL);
					}
					// destroy it
					m_world.DestroyBody(rb->body);
					entity.destroy();

					break;
				}
				else {
					if (!AudioDatabase::getInstance().isPlaying(SOUND_BIRD_COLLISION)) {
						AudioDatabase::getInstance().play(SOUND_BIRD_COLLISION);
					}
				}
			}
			else if (entity.has_component<Obstacle>()) {
				if (std::abs(velocity.x) > 10 || std::abs(velocity.y) > 10) {
					if (!AudioDatabase::getInstance().isPlaying(SOUND_WOOD_DESTROYED)) {
						AudioDatabase::getInstance().play(SOUND_WOOD_DESTROYED);
					}
					// creating a puff effect when an obstacle is destroyed.
					// since the obstacles are in different texture than the puff effect
					// we are creating a new entity with a sprite from the puff effect's texture
					auto puffCloud = entities.create();
					puffCloud.addComponent<Transform>(entity.getComponent<Transform>()->position);
					puffCloud.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")),
					                               true);
					auto animator = puffCloud.addComponent<Animator>(
						AnimatorsDatabase::getInstance().fromTypeToAnimator(PigMinion));
					animator->currentAnimation = PigDisappearing;

					m_world.DestroyBody(rb->body);
					entity.destroy();

					break;
				}
			}
		}
		// update the transform component
		if (rb->body->IsAwake()) {
			entityx::ComponentHandle<Transform> t = entity.getComponent<Transform>();
			b2Vec2 p = rb->body->GetPosition();

			t->position = Vector3f(p.x, p.y, 0);
			t->eulerAngles = Vector3f(0, 0, rb->body->GetAngle() * MathUtils::RAD2DEG);
			t->hasChanged = true;

		}
	}
#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
	m_debugDraw.Clear();
	m_world.DebugDraw();
	m_debugDraw.BufferData();
#endif
}

#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
b2draw::DebugDraw* PhysicsSystem2D::getDebugDraw() {
	return &m_debugDraw;
}
#endif
