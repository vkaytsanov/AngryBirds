#include <GL/glew.h>
#include <iostream>
#include "include/graphics.h"
#include "../../src/core/data/include/config_development.h"

Graphics::Graphics() : Graphics(new Configuration()) {
}

Graphics::Graphics(Configuration* config) : m_pConfig(config),
#if !defined(__EMSCRIPTEN__)
                                            m_pContext(nullptr),
                                            m_pWindow(nullptr),
                                            m_pScreenSurface(nullptr),
                                            m_pRenderer(nullptr),
#endif
                                            m_background(false),
                                            m_visible(true) {

}

void Graphics::updateTime() {
	// calculating the delta time
	uint32_t time = SDL_GetTicks();
	m_deltaTime = (static_cast<float>(time - m_lastTime)) / 1000.0f;
	m_lastTime = time;

	// calculating m_fps
	if (time - m_frameStart >= 1000) {
		m_fps = m_frames;
		m_frames = 0;
		m_frameStart = time;
	}
	m_frames++;
}

int Graphics::getWidth() const {
	return m_pConfig->width;
}

int Graphics::getHeight() const {
	return m_pConfig->height;
}

float Graphics::getDeltaTime() const {
	return m_deltaTime;
}

float Graphics::getFps() const {
	return m_fps;
}

void Graphics::createWindow() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL INIT ERROR " << SDL_GetError() << "\n";
		exit(-1);
	}
	
#if defined(__EMSCRIPTEN__)
	emscripten_set_canvas_element_size("#canvas", m_pConfig->width, m_pConfig->height);
	emscripten_webgl_init_context_attributes(&attr);
	attr.alpha = attr.depth = attr.stencil = attr.antialias =
		attr.preserveDrawingBuffer = attr.failIfMajorPerformanceCaveat = 0;
	attr.enableExtensionsByDefault = 1;
	attr.premultipliedAlpha = 0;
	attr.majorVersion = 2;
	attr.minorVersion = 0;
	ctx = emscripten_webgl_create_context("#canvas", &attr);
	emscripten_webgl_make_context_current(ctx);
#else
	// Decide OpenGL and GLSL versions
#if defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    m_glslVersion = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	m_glslVersion = "#version 330 core";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
#endif
	//Create m_pWindow
	m_pWindow = SDL_CreateWindow(m_pConfig->title,
	                             m_pConfig->x,
	                             m_pConfig->y,
	                             m_pConfig->width,
	                             m_pConfig->height,
	                             m_pConfig->isVisible | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (m_pWindow == nullptr) {
		std::cout << SDL_GetError() << "\n";
		exit(-1);
	}

	//Create the m_pContext for OpenGL
	m_pContext = SDL_GL_CreateContext(m_pWindow);


	if (!m_pContext) {
		std::cout << "SDL2 CONTEXT ERROR: " << SDL_GetError() << "\n";
		exit(-1);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_MakeCurrent(m_pWindow, m_pContext);

	// refresh rate synchronized to the monitor
	SDL_GL_SetSwapInterval(1);


	//Get m_pWindow surface
	m_pScreenSurface = SDL_GetWindowSurface(m_pWindow);
	if (m_pScreenSurface == nullptr) {
		std::cout << "SDL2 SCREEN SURFACE ERROR: " << SDL_GetError() << "\n";
		exit(-1);
	}
	//Update the surface
	SDL_UpdateWindowSurface(m_pWindow);
	//Create m_pRenderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	if (m_pRenderer == nullptr) {
		std::cout << "SDL2 RENDERER ERROR: " << SDL_GetError() << "\n";
	}
	

	
#endif
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << glewGetErrorString(err) << "\n";
	}
	int flags = IMG_INIT_PNG;

	//Create Image Handling, but just PNG format
	if (!IMG_Init(flags)) {
		std::cout << "SDL IMG Error: " << IMG_GetError() << "\n";
		exit(-1);
	}

	if (TTF_Init() == -1) {
		std::cout << "SDL2 TTF ERROR: " << TTF_GetError() << "\n";
		exit(-1);
	}

}

void Graphics::update() {
#if !defined(__EMSCRIPTEN__)
	SDL_UpdateWindowSurface(m_pWindow);
#endif
}

Graphics::~Graphics() {
#if !defined(__EMSCRIPTEN__)
	//Destroy openGL m_pContext
	SDL_GL_DeleteContext(m_pContext);
	//Destroy surface
	SDL_FreeSurface(m_pScreenSurface);
	m_pScreenSurface = nullptr;
	//Destroy m_pRenderer
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = nullptr;
	//Destroy m_pWindow
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
#endif
	//Shutdown SDL_TTF
	TTF_Quit();
	//Shut down SDL_Image
	IMG_Quit();
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Renderer* Graphics::getRenderer() const {
#if !defined(__EMSCRIPTEN__)
	return m_pRenderer;
#endif
}

void Graphics::setWidth(const int width) const {
	m_pConfig->width = width;
}

void Graphics::setHeight(const int height) const {
	m_pConfig->height = height;
}

bool Graphics::isBackground() const {
	return m_background;
}

void Graphics::setBackground(const bool background) {
	m_background = background;
}

bool Graphics::isVisible() const {
	return m_visible;
}

void Graphics::setVisible(const bool visible) {
	m_visible = visible;
}

SDL_Window* Graphics::getWindow() const {
	#if !defined(__EMSCRIPTEN__)
	return m_pWindow;
#endif
}

SDL_Surface* Graphics::getScreenSurface() const {
	#if !defined(__EMSCRIPTEN__)
	return m_pScreenSurface;
#endif
}

SDL_GLContext Graphics::getContext() const {
	#if !defined(__EMSCRIPTEN__)
	return m_pContext;
#endif
}

const char* Graphics::getGlslVersion() const {
	return m_glslVersion.c_str();
}
