#pragma once
#include "entity_type.h"
#include "../../components/2d/include/animator.h"

enum PigStates : int {
	PigIdle,
	PigLaughing,
	PigColliding,
	PigDisappearing
};

enum BirdStates : int {
	BirdIdle,
	BirdFlying,
	BirdColliding
};


class AnimatorsDatabase {
private:
	std::array<Animator, ENTITY_TYPE_SIZE> m_animators;
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
	Animator& fromTypeToAnimator(EntityType type);
	static AnimatorsDatabase& getInstance();
};
