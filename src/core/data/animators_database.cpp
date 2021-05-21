#include <box2d/b2_contact.h>

#include "include/animators_database.h"
#include "../components/2d/include/rigid_body_2d.h"

AnimatorsDatabase::AnimatorsDatabase() {
	initializePig();
	initializeTerence();
	initializeChuck();
	initializeRed();
	initializePuffCloud();
}


void AnimatorsDatabase::initializePig() {
	const std::shared_ptr<Texture> texture = AssetManager::getInstance().getSprite("all-in-one");
	{
		std::vector<Sprite> frames;
		frames.emplace_back(Sprite(TextureRegion(texture, 683, 684, 95, 96)));
		frames.emplace_back(Sprite(TextureRegion(texture, 585, 684, 95, 96)));

		Animation idlePigAnimation = Animation({5.0f, 1.0f}, std::move(frames), true);
		m_pigAnimator.animations.push_back(std::move(idlePigAnimation));
	}
	{
		std::vector<Sprite> frames;
		frames.emplace_back(Sprite(TextureRegion(texture, 373, 981, 95, 96)));

		Animation laughingPigAnimation = Animation(1.0f, std::move(frames), false);
		m_pigAnimator.animations.push_back(std::move(laughingPigAnimation));
	}

	{
		std::vector<Sprite> frames;
		frames.emplace_back(Sprite(TextureRegion(texture, 879, 683, 96, 96)));
		frames.emplace_back(Sprite(TextureRegion(texture, 373, 782, 96, 96)));

		Animation collidingPigAnimation = Animation({5.0f, 1.0f}, std::move(frames), true);
		m_pigAnimator.animations.push_back(std::move(collidingPigAnimation));
	}

	StateHandler idleHandler = [](entityx::Entity entity, int& currentState) {
		if (entity.getComponent<RigidBody2D>()->body->GetContactList() != nullptr) {
			currentState = PigColliding;
		}
	};
	StateHandler laughingHandler = [](entityx::Entity entity, int& currentState) {
		if (entity.getComponent<Animator>()->animations[currentState].isFinished()) {
			currentState = PigIdle;
		}
	};
	StateHandler collidingHandler = [](entityx::Entity entity, int& currentState) {
	};
	m_pigAnimator.conditions.push_back(std::move(idleHandler));
	m_pigAnimator.conditions.push_back(std::move(laughingHandler));
	m_pigAnimator.conditions.push_back(std::move(collidingHandler));
	m_pigAnimator.currentAnimation = 0;

}

void AnimatorsDatabase::initializeTerence() {
	addBirdIdleAnimation(m_terenceAnimator, 470, 783, 102, 94);
	addBirdFlyingAnimation(m_terenceAnimator, 675, 783, 102, 94);
	addBirdCollidingAnimation(m_terenceAnimator, 572, 783, 102, 94);
	m_terenceAnimator.entityType = Terence;
}

void AnimatorsDatabase::initializeChuck() {
	addBirdIdleAnimation(m_chuckAnimator, 734, 1305, 63, 54);
	addBirdFlyingAnimation(m_chuckAnimator, 734, 1247, 63, 54);
	addBirdCollidingAnimation(m_chuckAnimator, 734, 1363, 63, 54);
	m_chuckAnimator.entityType = Chuck;
}

void AnimatorsDatabase::initializeRed() {
	addBirdIdleAnimation(m_redAnimator, 1021, 1238, 44, 44);
	addBirdFlyingAnimation(m_redAnimator, 1067, 1238, 44, 44);
	addBirdCollidingAnimation(m_redAnimator, 961, 1283, 44, 44);
	m_redAnimator.entityType = Red;
}

void AnimatorsDatabase::initializePuffCloud() {
	std::vector<Sprite> frames;
	frames.emplace_back(
		Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 87, 1416, 40, 40)));
	frames.emplace_back(
		Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 1061, 83, 80, 73)));
	frames.emplace_back(
		Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 556, 877, 96, 93)));
	frames.emplace_back(
		Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 132, 933, 115, 111)));
	frames.emplace_back(
		Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 601, 161, 131, 129)));
	frames.emplace_back(
		Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 130, 445, 143, 137)));

	Animation puffAnimation = Animation(0.1f, std::move(frames), false);

	StateHandler puffHandler = [](entityx::Entity entity, int& currentState) {
		if (entity.getComponent<Animator>()->animations[currentState].isFinished()) {
			entity.destroy();
		}
	};
	m_pigAnimator.animations.push_back(std::move(puffAnimation));
	m_pigAnimator.conditions.push_back(std::move(puffHandler));
}

void AnimatorsDatabase::addBirdIdleAnimation(Animator& animator, int x, int y, int width, int height) {
	const std::shared_ptr<Texture> texture = AssetManager::getInstance().getSprite("all-in-one");
	std::vector<Sprite> frames;
	frames.emplace_back(Sprite(TextureRegion(texture, x, y, width, height)));

	Animation idle = Animation(1.0f, std::move(frames), false);
	animator.animations.push_back(std::move(idle));

	StateHandler idleHandler = [](entityx::Entity entity, int& currentState) {
		if (entity.getComponent<RigidBody2D>()->body->GetLinearVelocity().y != 0.0f) {
			currentState = BirdFlying;
		}
	};
	animator.conditions.push_back(std::move(idleHandler));
}

void AnimatorsDatabase::addBirdFlyingAnimation(Animator& animator, int x, int y, int width, int height) {
	const std::shared_ptr<Texture> texture = AssetManager::getInstance().getSprite("all-in-one");
	std::vector<Sprite> frames;
	frames.emplace_back(Sprite(TextureRegion(texture, x, y, width, height)));

	Animation flying = Animation(1.0f, std::move(frames), false);
	animator.animations.push_back(std::move(flying));

	StateHandler flyingHandler = [](entityx::Entity entity, int& currentState) {
		if (entity.getComponent<RigidBody2D>()->body->GetContactList() != nullptr) {
			currentState = BirdColliding;
		}
	};
	animator.conditions.push_back(std::move(flyingHandler));
}

void AnimatorsDatabase::addBirdCollidingAnimation(Animator& animator, int x, int y, int width, int height) {
	const std::shared_ptr<Texture> texture = AssetManager::getInstance().getSprite("all-in-one");
	std::vector<Sprite> frames;
	frames.emplace_back(Sprite(TextureRegion(texture, x, y, width, height)));

	Animation colliding = Animation(1.0f, std::move(frames), false);
	animator.animations.push_back(std::move(colliding));

	StateHandler collidingHandler = [](entityx::Entity entity, int& currentState) {
	};
	animator.conditions.push_back(std::move(collidingHandler));
}

Animator& AnimatorsDatabase::fromTypeToAnimator(EntityType type) {
	switch (type) {
		case PigMinion:
			return m_pigAnimator;
		case Terence:
			return m_terenceAnimator;
		case Chuck:
			return m_chuckAnimator;
		case Red:
			return m_redAnimator;
		default:
			Lib::app->error("AnimatorsDatabase", "couldn't deserialize type");
			return m_pigAnimator;
	}
}


AnimatorsDatabase& AnimatorsDatabase::getInstance() {
	static AnimatorsDatabase animDb;
	return animDb;
}
