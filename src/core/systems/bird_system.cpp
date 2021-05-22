#include "include/bird_system.h"

#include <box2d/b2_world.h>

#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/animator.h"
#include "../components/include/bird.h"
#include "../components/include/transform.h"
#include "../data/include/animators_database.h"
#include "include/lib.h"
#include "utils/include/viewport.h"
#include "../events/the_bird_is_gone.h"
#include "../events/round_over.h"

void BirdSystem::handleSlingshotInput() {
	if (Lib::input->isMouseLeftClick() && m_canSlingshot) {
		if (m_birds.empty()) return;
		m_currentBird = m_birds.front();
		const Vector2i mousePos = Viewport::fromScreenToViewport(Lib::input->getCurrMousePos());
		auto rigidBody = m_currentBird.getComponent<RigidBody2D>();
		const b2Fixture fixture = rigidBody->body->GetFixtureList()[0];
		b2Vec2 newPositon = {static_cast<float>(mousePos.x), -static_cast<float>(mousePos.y)};
		if (fixture.TestPoint(newPositon) || m_selected) {
			m_selected = true;
			newPositon = MathUtils::clamp(newPositon, m_slingShotStartPos - m_maxStretchDistance,
			                              m_slingShotStartPos + m_maxStretchDistance);
			// update the position according to the mouse position
			rigidBody->body->SetTransform(newPositon, rigidBody->body->GetAngle());
			m_currentBird.getComponent<Transform>()->position = Vector3f(newPositon.x, newPositon.y, 0);
			m_currentBird.getComponent<Transform>()->hasChanged = true;
			// Lib::app->log("BirdSystem", "Bird is selected. ");
		}
	}
	else {
		if (m_selected) {
			// cant send another bird without the current one colliding
			m_canSlingshot = false;
			m_selected = false;
			m_isFlying = true;
			m_birds.pop();
			Vector2i mouse = Viewport::fromScreenToViewport(Lib::input->getCurrMousePos());
			b2Vec2 force = -forceMultiplier * (b2Vec2(static_cast<float>(mouse.x), -static_cast<float>(mouse.y)) -
				m_slingShotStartPos);
			auto rigidBody = m_currentBird.getComponent<RigidBody2D>()->body;
			rigidBody->ApplyForceToCenter({force.x, force.y}, true);
			rigidBody->SetGravityScale(1);
		}
	}
}

void BirdSystem::handleBirdAbilityInput() {
	if (Lib::input->isMouseLeftClick() && m_isFlying) {
		if (!m_currentBird.valid()) return;

		switch (m_currentBird.getComponent<Bird>()->type) {
		case Chuck:
			useChuckAbility();
			break;
		case Red:
			useRedAbility();
			break;
		case Terence:
			break;
		case JayJakeJim:
		default:
			Lib::app->error("BirdAbility", "not implemented for the type");
			break;
		}
	}
}

void BirdSystem::updateCurrentBird(entityx::EventManager& events) {
	if (!m_currentBird.valid() || !m_isFlying) return;
	auto rb = m_currentBird.getComponent<RigidBody2D>()->body;
	if(!rb->GetContactList()) return;
	// if the bird has done its job and nearly stops moving
	// we destroy it and continue with the game logic
	if (rb->GetLinearVelocity().x < 5.0f) {
		// submit event for the particle system
		events.post<TheBirdIsGone>(TheBirdIsGone(m_currentBird.getComponent<Bird>()->type, rb->GetPosition()));
		// destroy it
		rb->GetWorld()->DestroyBody(rb);
		m_currentBird.destroy();
		// prepare next bird to the slingshot
		prepareNewBird(events);
		// we can interact with the slingshot again
		m_canSlingshot = true;
		m_isFlying = false;
	}
}

/* Heavily speeds up when the screen is tapped */
void BirdSystem::useChuckAbility() {
	const b2Vec2 force = b2Vec2(10'000, 0);
	m_currentBird.getComponent<RigidBody2D>()->body->ApplyForceToCenter(force, false);
}

/* Shoots red soundwaves which can be used to topple structures */
void BirdSystem::useRedAbility() {
	Lib::app->error("useRedAbility", "not implemented");
}

void BirdSystem::prepareNewBird(entityx::EventManager& events) {
	if(m_birds.empty()) {
		events.post<RoundOver>();
		// round is over
		return;
	}
	
	m_currentBird = m_birds.front();
	m_currentBird.getComponent<Transform>()->position = Vector3f(m_slingShotStartPos.x, m_slingShotStartPos.y, 0);
}

void BirdSystem::addBird(entityx::EntityManager& entities, EntityType type) {
	auto bird = entities.create();
	if (m_birds.empty()) {
		bird.addComponent<Transform>()->position = Vector3f(m_slingShotStartPos.x, m_slingShotStartPos.y, 0);
	}
	else {
		bird.addComponent<Transform>()->position = Vector3f(
			m_slingShotStartPos.x - static_cast<float>(15u * m_birds.size()), m_slingShotStartPos.y - 15.0f, 0);
	}
	bird.addComponent<Bird>(type);
	bird.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("all-in-one")), true);
	bird.addComponent<Animator>(AnimatorsDatabase::getInstance().fromTypeToAnimator(type));
	bird.addComponent<RigidBody2D>(Box2dDatabase::getInstance().fromTypeToBody(type));
	m_birds.push(bird);
}

void BirdSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
}

void BirdSystem::configure(entityx::EventManager& events) {
}

void BirdSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void BirdSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	handleSlingshotInput();
	handleBirdAbilityInput();
	updateCurrentBird(events);
}


void BirdSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
}
