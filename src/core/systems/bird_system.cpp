#include "include/bird_system.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/animator.h"
#include "../components/include/transform.h"
#include "../data/include/animators_database.h"
#include "include/lib.h"
#include "utils/include/viewport.h"

bool BirdSystem::m_canSlingshot = true;

void BirdSystem::handleInput() {
	if (Lib::input->isMouseLeftClick() && m_canSlingshot) {
		if (m_birds.empty()) return;
		entityx::Entity nextBird = m_birds.front();
		const Vector2i mousePos = Viewport::fromScreenToViewport(Lib::input->getCurrMousePos());
		auto rigidBody = nextBird.getComponent<RigidBody2D>();
		const b2Fixture fixture = rigidBody->body->GetFixtureList()[0];
		b2Vec2 newPositon = {static_cast<float>(mousePos.x), -static_cast<float>(mousePos.y)};
		if (fixture.TestPoint(newPositon) || m_selected) {
			m_selected = true;
			newPositon = MathUtils::clamp(newPositon, m_slingShotStartPos - m_maxStretchDistance,
			                              m_slingShotStartPos + m_maxStretchDistance);
			rigidBody->body->SetTransform(newPositon, rigidBody->body->GetAngle());
			nextBird.getComponent<Transform>()->position = Vector3f(newPositon.x, newPositon.y, 0);
			nextBird.getComponent<Transform>()->hasChanged = true;
			Lib::app->log("BirdSystem", "Bird is selected. ");
		}
	}
	else {
		if (m_selected) {
			// cant send another bird without the current one colliding
			// will be updated from #PhysicsSystem2D
			m_canSlingshot = false;
			m_selected = false;
			// slingshot the bird
			entityx::Entity nextBird = m_birds.front();
			m_birds.pop();
			Vector2i mouse = Viewport::fromScreenToViewport(Lib::input->getCurrMousePos());
			b2Vec2 force = -forceMultiplier * (b2Vec2(static_cast<float>(mouse.x), -static_cast<float>(mouse.y)) -
				m_slingShotStartPos);
			auto rigidBody = nextBird.getComponent<RigidBody2D>()->body;
			rigidBody->ApplyForceToCenter({force.x, force.y}, true);
			rigidBody->SetGravityScale(1);
		}
	}
}

/* Heavily speeds up when the screen is tapped */
void BirdSystem::useChuckAbility() {
	const b2Vec2 force = b2Vec2(10'000, 0);
	m_currentBird.getComponent<RigidBody2D>()->body->ApplyForceToCenter(force, false);
}

void BirdSystem::addBird(entityx::EntityManager& entities, EntityType type) {
	auto bird = entities.create();
	if (m_birds.empty()) {
		bird.addComponent<Transform>()->position = Vector3f(m_slingShotStartPos.x, m_slingShotStartPos.y, 0);
	}
	else {
		bird.addComponent<Transform>()->position = Vector3f(m_slingShotStartPos.x - static_cast<float>(15u * m_birds.size()), m_slingShotStartPos.y - 15.0f, 0);
	}
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
	handleInput();
}


void BirdSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
}
