#include "include/gles_graphics.h"

#include <iostream>



GLESGraphics::GLESGraphics(Configuration* config) : IGraphics(config){
}

void GLESGraphics::initialize() {
#if defined(__EMSCRIPTEN__)
	EMSCRIPTEN_RESULT r = emscripten_set_canvas_element_size("#canvas", m_pConfig->width, m_pConfig->height);
	if (r != EMSCRIPTEN_RESULT_SUCCESS){
		std::cout << "emscripten_set_canvas_element_size error \n";
	}

	emscripten_webgl_init_context_attributes(&attr);
	attr.alpha = attr.depth = attr.stencil = attr.antialias =
		attr.preserveDrawingBuffer = attr.failIfMajorPerformanceCaveat = 0;
	attr.enableExtensionsByDefault = 1;
	attr.premultipliedAlpha = 0;
	attr.majorVersion = 2;
	attr.minorVersion = 0;
	ctx = emscripten_webgl_create_context("#canvas", &attr);
	emscripten_webgl_make_context_current(ctx);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
	int flags = IMG_INIT_PNG;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	//Create Image Handling, but just PNG format
	if (!IMG_Init(flags)) {
		std::cout << "SDL IMG Error: " << IMG_GetError() << "\n";
		exit(-1);
	}
	std::cout << "WebGL Version: " << glGetString(GL_VERSION) << "\n";
}

void GLESGraphics::swapBuffers(Listener* listener) {
}

GLESGraphics::~GLESGraphics()
{
	//Shut down SDL_Image
	IMG_Quit();
	//Quit SDL subsystems
	SDL_Quit();
}
