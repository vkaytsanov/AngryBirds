#include "include/bird_system.h"


#include "box2d-emscripten/Dynamics/b2World.h"

#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/animator.h"
#include "../components/include/bird.h"
#include "../components/include/transform.h"
#include "../data/include/entity_factory.h"
#include "../data/include/audio_database.h"
#include "include/lib.h"
#include "utils/include/viewport.h"
#include "../events/the_bird_is_gone.h"
#include "../events/round_over.h"


struct Pig;

void BirdSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	events.subscribe<TheBirdIsGone>(*this);
}

void BirdSystem::configure(entityx::EventManager& events) {
}

void BirdSystem::receive(const TheBirdIsGone& event) {
	// we can interact with the slingshot again
	m_canSlingshot = true;
	m_isFlying = false;
	m_abilityUsed = false;
	m_eventProcessed = false;
}

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
			if (!m_playedSelectedSound) {
				m_playedSelectedSound = true;
				AudioDatabase::getInstance().play(SOUND_BIRD_SELECT);
			}
			newPositon = MathUtils::clamp(newPositon, m_slingPos - m_maxDistance, m_slingPos + m_maxDistance);
			// update the position according to the mouse position
			rigidBody->body->SetTransform(newPositon, rigidBody->body->GetAngle());
			m_currentBird.getComponent<Transform>()->position = Vector3f(newPositon.x, newPositon.y, 0);
			m_currentBird.getComponent<Transform>()->hasChanged = true;
		}
	}
	else if (m_selected) {
		// cant send another bird without the current one colliding
		m_canSlingshot = false;
		m_selected = false;
		m_playedSelectedSound = false;
		m_isFlying = true;

		auto rigidBody = m_currentBird.getComponent<RigidBody2D>()->body;
		b2Vec2 force = -m_forceMultiplier * (rigidBody->GetPosition() - m_slingPos);
		if (m_currentBird.getComponent<Bird>()->type == Terence) force *= 4;


		rigidBody->ApplyForceToCenter({force.x, force.y});
		rigidBody->SetGravityScale(1);

		m_birds.pop();
		AudioDatabase::getInstance().play(SOUND_BIRD_FLYING);
	}

}

void BirdSystem::handleBirdAbilityInput() {
	if (Lib::input->isMouseLeftClick() && m_isFlying && !m_abilityUsed) {
		m_abilityUsed = true;
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

/* Heavily speeds up when the screen is tapped */
void BirdSystem::useChuckAbility() {
	const b2Vec2 force = b2Vec2(50'000, 0);

	m_currentBird.getComponent<RigidBody2D>()->body->ApplyForceToCenter({force.x, force.y});

}

/* Shoots red soundwaves which can be used to topple structures */
void BirdSystem::useRedAbility() {
	Lib::app->error("useRedAbility", "not implemented");
}

void BirdSystem::prepareNewBird(entityx::EntityManager& entities, entityx::EventManager& events) {
	if (m_eventProcessed) return;
	m_eventProcessed = true;

	if (m_birds.empty()) {
		events.post<RoundOverEvent>(false);
		// round is over
		return;
	}

	m_currentBird = m_birds.front();
	auto rb = m_currentBird.getComponent<RigidBody2D>()->body;
	rb->SetTransform(m_slingPos, rb->GetAngle());

	auto transform = m_currentBird.getComponent<Transform>();
	transform->position = Vector3f(m_slingPos.x, m_slingPos.y, 0);
	transform->hasChanged = true;

}

void BirdSystem::addBird(entityx::EntityManager& entities, EntityType type) {
	auto bird = EntityFactory::createEntityFromType(entities, type);
	auto transform = bird.getComponent<Transform>();
	if (m_birds.empty()) {
		transform->position = Vector3f(m_slingPos.x, m_slingPos.y, 0);
	}
	else {
		transform->position = Vector3f(
			m_slingPos.x - static_cast<float>(17u * m_birds.size()), m_slingPos.y - 4.f, 0);
	}
	m_birds.push(bird);
}

void BirdSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	handleSlingshotInput();
	handleBirdAbilityInput();
	// check the current if it is in bounds
	if (m_isFlying) {
		auto transform = m_currentBird.getComponent<Transform>();
		if (transform->position.x < -Viewport::m_worldWidth / 2 || transform->position.x > Viewport::m_worldWidth / 2) {
			// destroy it
			auto rb = m_currentBird.getComponent<RigidBody2D>()->body;
			rb->GetWorld()->DestroyBody(rb);
			m_currentBird.destroy();
			// don't send event, but process it in the bird system
			receive({});
		}
	}
	// when we receive event that we need to prepare new bird
	prepareNewBird(entities, events);
}
