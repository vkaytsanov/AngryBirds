#include "include/animators_database.h"

#include <box2d/b2_contact.h>

#include "../components/2d/include/rigid_body_2d.h"


AnimatorsDatabase::AnimatorsDatabase() {
	initializePig();
	initializeRedBirdBig();
}

void AnimatorsDatabase::initializePig() {
	{
		std::vector<Sprite> frames;
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 683, 684, 95, 96)));
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 585, 684, 95, 96)));

		Animation idlePigAnimation = Animation({5.0f, 1.0f}, std::move(frames), true);
		m_pigAnimator.animations.push_back(std::move(idlePigAnimation));
	}
	{
		std::vector<Sprite> frames;
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 373, 981, 95, 96)));

		Animation laughingPigAnimation = Animation(1.0f, std::move(frames), false);
		m_pigAnimator.animations.push_back(std::move(laughingPigAnimation));
	}
	
	{
		std::vector<Sprite> frames;
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 879, 683, 96, 96)));
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 373, 782, 96, 96)));

		Animation collidingPigAnimation = Animation({5.0f, 1.0f}, std::move(frames), true);
		m_pigAnimator.animations.push_back(std::move(collidingPigAnimation));
	}
	
	ConditionalDef idleHandler = [](entityx::Entity entity, int& currentState) {
		if (entity.getComponent<RigidBody2D>()->body->GetContactList() != nullptr) {
			currentState = PigColliding;
		}
	};
	ConditionalDef laughingHandler = [](entityx::Entity entity, int& currentState) {
		if (entity.getComponent<Animator>()->animations[currentState].isFinished()) {
			currentState = PigIdle;
		}
	};
	ConditionalDef collidingHandler = [](entityx::Entity entity, int& currentState) {
	};
	m_pigAnimator.conditions.push_back(std::move(idleHandler));
	m_pigAnimator.conditions.push_back(std::move(laughingHandler));
	m_pigAnimator.conditions.push_back(std::move(collidingHandler));
	m_pigAnimator.currentAnimation = 0;
	
}

void AnimatorsDatabase::initializeRedBirdBig() {
	{
		std::vector<Sprite> frames;
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 470, 783, 102, 94)));

		Animation redBirdBigIdleAnimation = Animation(1.0f, std::move(frames), false);
		m_redBirdBigAnimator.animations.push_back(std::move(redBirdBigIdleAnimation));
	}
	{
		std::vector<Sprite> frames;
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 674, 783, 102, 94)));

		Animation redBirdFlyingAnimation = Animation(1.0f, std::move(frames), false);
		m_redBirdBigAnimator.animations.push_back(std::move(redBirdFlyingAnimation));
	}
	{
		std::vector<Sprite> frames;
		frames.emplace_back(
			Sprite(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 572, 783, 102, 94)));

		Animation redBirdBigCollidingAnimation = Animation(1.0f, std::move(frames), false);
		m_redBirdBigAnimator.animations.push_back(std::move(redBirdBigCollidingAnimation));
	}
	{
		ConditionalDef idleHandler = [](entityx::Entity entity, int& currentState) {
			if (entity.getComponent<RigidBody2D>()->body->GetLinearVelocity().y != 0.0f) {
				currentState = BirdFlying;
			}
		};
		ConditionalDef flyingHandler = [](entityx::Entity entity, int& currentState) {
			if (entity.getComponent<RigidBody2D>()->body->GetContactList() != nullptr) {
				currentState = BirdColliding;
			}
		};
		ConditionalDef collidingHandler = [](entityx::Entity entity, int& currentState) {
		};
		m_redBirdBigAnimator.conditions.push_back(std::move(idleHandler));
		m_redBirdBigAnimator.conditions.push_back(std::move(flyingHandler));
		m_redBirdBigAnimator.conditions.push_back(std::move(collidingHandler));
		m_redBirdBigAnimator.currentAnimation = 0;
	}
}


AnimatorsDatabase& AnimatorsDatabase::getInstance() {
	static AnimatorsDatabase animDb;
	return animDb;
}
