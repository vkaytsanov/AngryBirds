#pragma once
#include "input.h"

#if defined(__EMSCRIPTEN__)
#include "emscripten.h"
#include "emscripten/html5.h"
#include "emscripten/html5_webgl.h"
#endif

class EmscriptenInput : public Input {
#if defined(__EMSCRIPTEN__)
	friend EM_BOOL mouseDownCallback(int eventType, const EmscriptenMouseEvent* event, void* userData);
	friend EM_BOOL mouseMoveCallback(int eventType, const EmscriptenMouseEvent* event, void* userData);
	friend EM_BOOL mouseUpCallback(int eventType, const EmscriptenMouseEvent* event, void* userData);
	friend EM_BOOL mouseClickCallback(int eventType, const EmscriptenMouseEvent* event, void* userData);
#endif
public:
	EmscriptenInput(const float width, const float height);
public:
	void update() override;
	void processEvents() override;
};
