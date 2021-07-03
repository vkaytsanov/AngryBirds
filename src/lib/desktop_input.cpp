#include "include/desktop_input.h"

#include <iostream>

#include "imgui/imgui_impl_sdl.h"
#include "include/lib.h"

DesktopInput::DesktopInput(const float width, const float height) : Input(width, height){
}

void DesktopInput::update() {
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

void DesktopInput::processEvents() {
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