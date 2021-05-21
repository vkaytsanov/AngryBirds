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
	void initializePig();
	void initializeTerence();
	void initializeChuck();
	void initializeRed();
	void initializePuffCloud();

	void addBirdIdleAnimation(Animator& animator, int x, int y, int width, int height);
	void addBirdFlyingAnimation(Animator& animator, int x, int y, int width, int height);
	void addBirdCollidingAnimation(Animator& animator, int x, int y, int width, int height);
public:
	Animator m_pigAnimator;
	Animator m_terenceAnimator;
	Animator m_chuckAnimator;
	Animator m_redAnimator;
public:
	AnimatorsDatabase();
	Animator& fromTypeToAnimator(EntityType type);
	static AnimatorsDatabase& getInstance();
};
