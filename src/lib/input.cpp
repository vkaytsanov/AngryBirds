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

void Input::update() {
	Lib::app->log("Input", "updating");
	while (SDL_PollEvent(&e) != 0) {
		
#if !defined(__EMSCRIPTEN__)
		ImGui_ImplSDL2_ProcessEvent(&e);
#else
		Lib::app->log("Input", "received input");
#endif
		//User requests to quit
		if (e.type == SDL_QUIT) {
			m_quit = true;
		}
		//User presses a key
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym > 322){
				std::cout << "key is not registered";
				continue;
			}
			m_keys[e.key.keysym.sym] = true;
			m_keyEvents.push(e);
		}
		//User releases a key
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym > 322){
				std::cout << "key is not registered";
				continue;
			}
			m_keys[e.key.keysym.sym] = false;
			m_keyEvents.push(e);
		}
			//User does action with the mouse
		else if (e.type == SDL_MOUSEMOTION) {
			m_mouseMoved = true;
			m_lastMousePosX = m_currMousePosX;
			m_lastMousePosY = m_currMousePosY;
			m_currMousePosX = e.motion.x;
			m_currMousePosY = e.motion.y;
			m_touchEvents.push(e);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				m_mouseLeftClick = true;
				m_lastMousePosX = m_currMousePosX;
				m_lastMousePosY = m_currMousePosY;
				m_currMousePosX = e.motion.x;
				m_currMousePosY = e.motion.y;
			}
			else if (e.button.button == SDL_BUTTON_RIGHT) {
				m_mouseRightClick = true;
				m_lastMousePosX = m_currMousePosX;
				m_lastMousePosY = m_currMousePosY;
				m_currMousePosX = e.motion.x;
				m_currMousePosY = e.motion.y;
			}
			//Lib::app->log("MouseEvent", "pushed");
			m_touchEvents.push(e);
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				m_mouseLeftClick = false;
				m_lastMousePosX = m_currMousePosX;
				m_lastMousePosY = m_currMousePosY;
				m_currMousePosX = e.motion.x;
				m_currMousePosY = e.motion.y;
			}
			else if (e.button.button == SDL_BUTTON_RIGHT) {
				m_mouseRightClick = false;
				m_lastMousePosX = m_currMousePosX;
				m_lastMousePosY = m_currMousePosY;
				m_currMousePosX = e.motion.x;
				m_currMousePosY = e.motion.y;
			}
			m_touchEvents.push(e);
		}
		else if (e.type == SDL_WINDOWEVENT) {
			switch (e.window.event) {
				case SDL_WINDOWEVENT_SHOWN:
					Lib::graphics->setBackground(false);
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					Lib::graphics->setBackground(true);
					break;
				case SDL_WINDOWEVENT_RESIZED:
					Lib::graphics->setWidth(e.window.data1);
					Lib::graphics->setHeight(e.window.data2);
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					Lib::graphics->setVisible(false);
					break;
				case SDL_WINDOWEVENT_RESTORED:
					Lib::graphics->setVisible(true);
					break;
			}
		}
	}
}

void Input::processEvents() {
	if (!m_pProcessor) {
		// Get rid of the events that happened, else we will get bombarded
		// with events after a InputProcessor gets used
		while (!m_keyEvents.empty()) {
			m_keyEvents.pop();
		}
		while (!m_touchEvents.empty()) {
			m_touchEvents.pop();
		}
		return;
	}
	while (!m_keyEvents.empty()) {
		SDL_Event event = m_keyEvents.front();
		m_keyEvents.pop();
		switch (event.type) {
			case SDL_KEYDOWN:
				m_pProcessor->keyDown(event, event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_pProcessor->keyUp(event, event.key.keysym.sym);
				break;

		}
	}
	while (!m_touchEvents.empty()) {
		SDL_Event event = m_touchEvents.front();
		m_touchEvents.pop();
		//Lib::app->log("MouseEvent", "popped");
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				m_pProcessor->touchDown(event, event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONUP:
				m_pProcessor->touchUp(event, event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEMOTION:
				break;
			default:
				Lib::app->debug("Input", "MouseEvent not registered.");
		}
	}
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
