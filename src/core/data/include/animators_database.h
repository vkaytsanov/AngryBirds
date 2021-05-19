#pragma once
#include "utils/include/animation.h"
#include "../../components/2d/include/animator.h"

enum AnimationType {
	Pig,
	RedBirdBig
};

enum PigStates : int {
	PigIdle,
	PigLaughing,
	PigColliding
};

enum BirdStates : int {
	BirdIdle,
	BirdFlying,
	BirdColliding
};


class AnimatorsDatabase {
private:
	void initializePig();
	void initializeRedBirdBig();
public:
	Animator m_pigAnimator;
	Animator m_redBirdBigAnimator;
public:
	AnimatorsDatabase();
	static AnimatorsDatabase& getInstance();
};
