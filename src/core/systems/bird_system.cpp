#include "include/bird_system.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "include/lib.h"
#include "utils/include/viewport.h"

bool BirdSystem::m_canSlingshot = true;

void BirdSystem::handleInput() {
	if(Lib::input->isMouseLeftClick() && m_canSlingshot) {
		if(m_birds.empty()) return;
		entityx::Entity nextBird = m_birds.front();
		const Vector2i mousePos = Viewport::fromScreenToViewport(Lib::input->getCurrMousePos());
		auto rigidBody = nextBird.getComponent<RigidBody2D>();
		const b2Fixture fixture = rigidBody->body->GetFixtureList()[0];
		const b2Vec2 newPositon = {static_cast<float>(mousePos.x), -static_cast<float>(mousePos.y)};
		if(fixture.TestPoint(newPositon)) {
			m_selected = true;
			rigidBody->body->SetTransform(newPositon, rigidBody->body->GetAngle());
			nextBird.getComponent<Transform>()->position = Vector3f(newPositon.x, newPositon.y, 0);
			nextBird.getComponent<Transform>()->hasChanged = true;
			Lib::app->log("BirdSystem", "Bird is selected. ");
		}
	}
	else {
		if(m_selected) {
			// cant send another bird without the current one colliding
			// will be updated from #PhysicsSystem2D
			m_canSlingshot = false;
			m_selected = false;
			// slingshot the bird
			entityx::Entity nextBird = m_birds.front();
			m_birds.pop();
			Vector2i mouse = Viewport::fromScreenToViewport(Lib::input->getCurrMousePos());
			Vector3f force = (Vector3f(mouse.x, -mouse.y, 0) - m_slingShotStartPos) * -forceMultiplier;
			auto rigidBody = nextBird.getComponent<RigidBody2D>()->body;
			rigidBody->ApplyForceToCenter({force.x, force.y}, true);
			rigidBody->SetGravityScale(1);
		}
	}
}

void BirdSystem::initializeCurrentRound(std::vector<entityx::Entity>& birds) {
	Vector3f tmp = m_slingShotStartPos;
	for(unsigned i = 0; i < birds.size(); i++) {
		m_birds.push(birds[i]);
		tmp.x -= 1;
	}
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
