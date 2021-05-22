#pragma once



enum EntityType {
	Terence = 0,
	Red = 1,
	Chuck = 2,
	JayJakeJim = 3,

	Undefined = 4,

	PigMinion = 5,

	WoodTriangle = 6,
	WoodSquare = 7,
	WoodRectangle = 8
	
};


constexpr int ENTITY_TYPE_SIZE = WoodRectangle + 1;

inline bool isBird(EntityType type) {
	return type < Undefined;
}

inline bool isPig(EntityType type) {
	return type == PigMinion;
}

inline bool isAnimated(EntityType type) {
	return type <= PigMinion;
}
