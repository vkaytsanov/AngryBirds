#pragma once
#include "input.h"

class DesktopInput : public Input{
private:
	SDL_Event e;
	std::queue<SDL_Event> m_keyEvents;
	std::queue<SDL_Event> m_touchEvents;
public:
	DesktopInput(const float width, const float height);
	void update() override;
	void processEvents() override;
};
