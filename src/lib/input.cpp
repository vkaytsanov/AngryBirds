#include "include/input.h"
#include <iostream>
#include "include/lib.h"
#include <cstring>
#include <memory>

#if !defined(__EMSCRIPTEN__)
#include "imgui/imgui_impl_sdl.h"
#endif

Input::Input(const float width, const float height) {
	std::memset(&m_keys[0], false, sizeof m_keys);
	m_lastMousePosX = m_currMousePosX = width / 2;
	m_lastMousePosY = m_currMousePosY = height / 2;
}

bool Input::shouldQuit() const {
	return m_quit;
}

bool Input::isKeyPressed(const char key) const {
	return m_keys[key];
}

bool Input::isMouseMoved() const {
	return m_mouseMoved;
}

float Input::getLastMousePosX() const {
	return m_lastMousePosX;
}

float Input::getLastMousePosY() const {
	return m_lastMousePosY;
}

float Input::getCurrMousePosX() const {
	return m_currMousePosX;
}

float Input::getCurrMousePosY() const {
	return m_currMousePosY;
}

Vector2i Input::getCurrMousePos() const {
	return Vector2i(m_currMousePosX, m_currMousePosY);
}


float Input::getMouseMoveX() const {
	return m_currMousePosX - m_lastMousePosX;
}

float Input::getMouseMoveY() const {
	return m_lastMousePosY - m_currMousePosY;
}

bool Input::isMouseLeftClick() const {
	return m_mouseLeftClick;
}

bool Input::isMouseRightClick() const {
	return m_mouseRightClick;
}

void Input::resetMouse() const {
	//SDL_WarpMouseInWindow(Lib::graphics->getWindow(), Lib::graphics->getWidth() / 2, Lib::graphics->getHeight() / 2);
}

float Input::getMouseDeltaX() const {
	return 0.5f * (m_currMousePosX - (float)Lib::graphics->getWidth() / 2);
}

float Input::getMouseDeltaY() const {
	return -0.5f * (m_currMousePosY - (float)Lib::graphics->getHeight() / 2);
}

void Input::setProcessor(InputProcessor* processor) {
	m_pProcessor = processor;
}

InputProcessor* Input::getProcessor() const {
	return m_pProcessor;
}
