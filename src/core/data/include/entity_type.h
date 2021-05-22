#pragma once

enum EntityType {
	Terence = -4,
	Red = -3,
	Chuck = -2,
	JayJakeJim = -1,

	Undefined = 0,

	PigMinion = 1
};

inline bool isBird(EntityType type) {
	return type < Undefined;
}

inline bool isPig(EntityType type) {
	return type > Undefined;
}
