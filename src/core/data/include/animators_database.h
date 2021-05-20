#pragma once
#include "prefab_database.h"
#include "../../components/2d/include/animator.h"

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
	Animator& fromTypeToAnimator(PrefabType type);
	static AnimatorsDatabase& getInstance();
};
