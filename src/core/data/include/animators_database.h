#pragma once

#include <array>

#include "entity_type.h"
#include "../../components/2d/include/animator.h"

enum PigStates : int {
	PigIdle,
	PigIdleLaughing,
	PigColliding,
	PigCollidingLaughing,
	PigDisappearing
};

enum BirdStates : int {
	BirdIdle,
	BirdFlying,
	BirdColliding
};

class AnimatorsDatabase {
private:
	std::array<Animator, PigMinion + 1> m_animators;
	void initializePig();
	void initializeTerence();
	void initializeChuck();
	void initializeRed();
	void initializePuffCloud();


	void addBirdIdleAnimation(Animator& animator, int x, int y, int width, int height);
	void addBirdFlyingAnimation(Animator& animator, int x, int y, int width, int height);
	void addBirdCollidingAnimation(Animator& animator, int x, int y, int width, int height);
public:
	AnimatorsDatabase();
	~AnimatorsDatabase();
public:
	Animator& fromTypeToAnimator(EntityType type);
	static AnimatorsDatabase& getInstance();
};
