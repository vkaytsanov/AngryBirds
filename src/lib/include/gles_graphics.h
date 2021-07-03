#pragma once
#include "graphics.h"

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#else
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
class Listener;

class GLESGraphics : public IGraphics {
private:
#if defined(__EMSCRIPTEN__)
	EmscriptenWebGLContextAttributes attr;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
#endif
public:
	explicit GLESGraphics(Configuration* config);
	~GLESGraphics() override;
public:
	void initialize() override;
	void swapBuffers(Listener* listener) override;
};
