#include "include/emscripten_input.h"
#include "include/lib.h"

/* mouse buttons*/
const int EMSCRIPTEN_LMB = 0;
const int EMSCRIPTEN_MMB = 1;
const int EMSCRIPTEN_RMB = 2;

EM_BOOL mouseDownCallback(int eventType, const EmscriptenMouseEvent* event, void* userData) {
	EmscriptenInput* input = static_cast<EmscriptenInput*>(userData);
	if(event->button == EMSCRIPTEN_LMB) {
		input->m_mouseLeftClick = true;
	}
	else if(event->button == EMSCRIPTEN_RMB) {
		input->m_mouseRightClick = true;
	}
	input->m_lastMousePosX = input->m_currMousePosX;
	input->m_lastMousePosY = input->m_currMousePosY;
	input->m_currMousePosX = static_cast<float>(event->targetX);
	input->m_currMousePosY = static_cast<float>(event->targetY);
	return EMSCRIPTEN_RESULT_SUCCESS;
}

EM_BOOL mouseClickCallback(int eventType, const EmscriptenMouseEvent* event, void* userData) {
	EmscriptenInput* input = static_cast<EmscriptenInput*>(userData);
	if(event->button == EMSCRIPTEN_LMB) {
		input->m_mouseLeftClick = true;
		Lib::app->log("Click", "Left");
	}
	else if(event->button == EMSCRIPTEN_RMB) {
		input->m_mouseRightClick = true;
		Lib::app->log("Click", "Right");
	}
	input->m_lastMousePosX = input->m_currMousePosX;
	input->m_lastMousePosY = input->m_currMousePosY;
	input->m_currMousePosX = static_cast<float>(event->targetX);
	input->m_currMousePosY = static_cast<float>(event->targetY);
	return EMSCRIPTEN_RESULT_SUCCESS;
}

EM_BOOL mouseMoveCallback(int eventType, const EmscriptenMouseEvent* event, void* userData) {
	EmscriptenInput* input = static_cast<EmscriptenInput*>(userData);
	input->m_mouseMoved = true;
	input->m_lastMousePosX = input->m_currMousePosX;
	input->m_lastMousePosY = input->m_currMousePosY;
	input->m_currMousePosX = static_cast<float>(event->targetX);
	input->m_currMousePosY = static_cast<float>(event->targetY);
	return EMSCRIPTEN_RESULT_SUCCESS;
}

EM_BOOL mouseUpCallback(int eventType, const EmscriptenMouseEvent* event, void* userData) {
	EmscriptenInput* input = static_cast<EmscriptenInput*>(userData);
	if(event->button == EMSCRIPTEN_LMB) {
		input->m_mouseLeftClick = false;
	}
	else if(event->button == EMSCRIPTEN_RMB) {
		input->m_mouseRightClick = false;
	}
	input->m_lastMousePosX = input->m_currMousePosX;
	input->m_lastMousePosY = input->m_currMousePosY;
	input->m_currMousePosX = static_cast<float>(event->targetX);
	input->m_currMousePosY = static_cast<float>(event->targetY);
	return EMSCRIPTEN_RESULT_SUCCESS;
}


EmscriptenInput::EmscriptenInput(const float width, const float height) : Input(width, height) {
	emscripten_set_mousedown_callback("#canvas", this, true, mouseDownCallback);
	emscripten_set_mousemove_callback("#canvas", this, true, mouseMoveCallback);
	emscripten_set_mouseup_callback("#canvas", this, true, mouseUpCallback);
	// intentionally commented
	//emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, mouseClickCallback);
}

void EmscriptenInput::update() {
}


void EmscriptenInput::processEvents() {
}
