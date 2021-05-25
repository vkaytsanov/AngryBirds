#pragma once
#include "entityx/Event.h"

struct RoundOverEvent : public entityx::Event<RoundOverEvent> {
	bool isWon;

	RoundOverEvent(bool isWon) : isWon(isWon){}
};