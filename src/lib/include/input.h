#ifndef INPUT
#define INPUT


#include <memory>
#include <queue>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "../utils/include/input_processor.h"
#include "utils/geometry/include/vector2.h"


class Input {
protected:
	bool m_quit = false;
	/* check SDL_KeyCode, max elements = 322 */
	bool m_keys[322];
	bool m_mouseMoved = false;
	bool m_mouseLeftClick = false;
	bool m_mouseRightClick = false;
	float m_lastMousePosX = 0;
	float m_lastMousePosY = 0;
	float m_currMousePosX = 0;
	float m_currMousePosY = 0;
	InputProcessor* m_pProcessor = nullptr;
public:
	Input(const float width, const float height);
public:
	virtual void update() = 0;
	virtual void processEvents() = 0;
	void resetMouse() const;
	bool shouldQuit() const;
	void setProcessor(InputProcessor* processor);
	InputProcessor* getProcessor() const;
	bool isKeyPressed(char key) const;
	bool isMouseMoved() const;
	float getLastMousePosX() const;
	float getLastMousePosY() const;
	float getCurrMousePosX() const;
	float getCurrMousePosY() const;
	Vector2i getCurrMousePos() const;
	float getMouseMoveX() const;
	float getMouseMoveY() const;
	float getMouseDeltaX() const;
	float getMouseDeltaY() const;
	bool isMouseLeftClick() const;
	bool isMouseRightClick() const;
};

#endif