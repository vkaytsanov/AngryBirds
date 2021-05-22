#pragma once



enum EntityType {
	Undefined = -1,
	
	Terence = 0,
	Red = 1,
	Chuck = 2,
	JayJakeJim = 3,

	PigMinion = 4,

	WoodTriangle = 5,
	WoodSquare = 6,
	WoodRectangle = 7
	
};

constexpr int ENTITY_TYPE_SIZE = WoodRectangle + 1;

inline bool isBird(EntityType type) {
	return type <= JayJakeJim;
}

inline bool isPig(EntityType type) {
	return type == PigMinion;
}

inline bool isAnimated(EntityType type) {
	return type <= PigMinion;
}
