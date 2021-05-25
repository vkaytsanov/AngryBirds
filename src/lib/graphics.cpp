#include <GL/glew.h>
#include <iostream>
#include "include/graphics.h"
#include "../../src/core/data/include/config_development.h"

Graphics::Graphics() : Graphics(new Configuration()) {
}

Graphics::Graphics(Configuration* config) : m_pConfig(config),
                                            m_pContext(nullptr),
                                            m_pWindow(nullptr),
                                            m_pScreenSurface(nullptr),
                                            m_pRenderer(nullptr),
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
		std::cout << SDL_GetError() << "\n";
	}
	else {
		int flags = IMG_INIT_PNG;
		
		//Create Image Handling, but just PNG format
		if (!IMG_Init(flags)) {
			std::cout << "SDL IMG Error: " << IMG_GetError() << "\n";
		}

	// Decide OpenGL and GLSL versions
#if defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    m_glslVersion = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#elif defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN_DEVELOPMENT)
    // GL 3.0 + GLSL 130
    m_glslVersion = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
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
		}
		else {
			//Create the m_pContext for OpenGL
			m_pContext = SDL_GL_CreateContext(m_pWindow);


			if (!m_pContext) {
				std::cout << SDL_GetError() << "\n";
			}
			else {
				// glewExperimental = GL_TRUE;
				GLenum err = glewInit();
				if (GLEW_OK != err) {
					std::cout << glewGetErrorString(err) << "\n";
				}
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
				SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
				
				SDL_GL_MakeCurrent(m_pWindow, m_pContext);
				
				std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
				// refresh rate synchronized to the monitor
				SDL_GL_SetSwapInterval(1);

			}

			//Get m_pWindow surface
			m_pScreenSurface = SDL_GetWindowSurface(m_pWindow);
			if (m_pScreenSurface == nullptr) {
				std::cout << SDL_GetError() << "\n";
			}
			else {
				//Update the surface
				SDL_UpdateWindowSurface(m_pWindow);
				//Create m_pRenderer
				m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
				if (m_pRenderer == nullptr) {
					std::cout << SDL_GetError() << "\n";
				}
			}
		}
		if (TTF_Init() == -1) {
			std::cout << TTF_GetError() << "\n";
		}

	}
}

void Graphics::update() {
	SDL_UpdateWindowSurface(m_pWindow);
}

Graphics::~Graphics() {
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
	//Shutdown SDL_TTF
	TTF_Quit();
	//Shut down SDL_Image
	IMG_Quit();
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Renderer* Graphics::getRenderer() const {
	return m_pRenderer;
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
	return m_pWindow;
}

SDL_Surface* Graphics::getScreenSurface() const {
	return m_pScreenSurface;
}

SDL_GLContext Graphics::getContext() const {
	return m_pContext;
}

const char* Graphics::getGlslVersion() const {
	return m_glslVersion.c_str();
}
