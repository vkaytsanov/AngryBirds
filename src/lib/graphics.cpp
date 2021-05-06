#include <GL/glew.h>
#include <iostream>
#include "include/graphics.h"


Graphics::Graphics() : Graphics(new Configuration()) {
}

Graphics::Graphics(Configuration* config) : m_pConfig(config),
                                            m_context(nullptr),
                                            m_window(nullptr),
                                            m_screenSurface(nullptr),
                                            m_renderer(nullptr),
                                            m_background(false),
                                            m_visible(true) {

}

void Graphics::updateTime() {
	// calculating the delta time
	uint64_t time = SDL_GetTicks();
	m_deltaTime = (time - m_lastTime) / 1000.0f;
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

float Graphics::getFps() {
	return m_fps;
}

void Graphics::createWindow() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << SDL_GetError() << "\n";
	}
	else {
		//Create Image Handling, but just PNG format
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			std::cout << IMG_GetError() << "\n";
		}
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201'703L) || __cplusplus >= 201'703L)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

		//Create m_window
		m_window = SDL_CreateWindow(m_pConfig->title,
		                            m_pConfig->x,
		                            m_pConfig->y,
		                            m_pConfig->width,
		                            m_pConfig->height,
		                            m_pConfig->isVisible | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		if (m_window == nullptr) {
			std::cout << SDL_GetError() << "\n";
		}
		else {
			//Create the m_context for OpenGL
			m_context = SDL_GL_CreateContext(m_window);


			if (!m_context) {
				std::cout << SDL_GetError() << "\n";
			}
			else {
				GLenum err = glewInit();
				if (GLEW_OK != err) {
					std::cout << glewGetErrorString(err) << "\n";
				}

				std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
				// refresh rate synchronized to the monitor
				SDL_GL_SetSwapInterval(1);

			}

			//Get m_window surface
			m_screenSurface = SDL_GetWindowSurface(m_window);
			if (m_screenSurface == nullptr) {
				std::cout << SDL_GetError() << "\n";
			}
			else {
				//Update the surface
				SDL_UpdateWindowSurface(m_window);
				//Create m_renderer
				m_renderer = SDL_CreateRenderer(m_window, -1, 0);
				if (m_renderer == nullptr) {
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
	SDL_UpdateWindowSurface(m_window);
}

Graphics::~Graphics() {
	//Destroy openGL m_context
	SDL_GL_DeleteContext(m_context);
	//Destroy surface
	SDL_FreeSurface(m_screenSurface);
	m_screenSurface = nullptr;
	//Destroy m_renderer
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	//Destroy m_window
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	//Shutdown SDL_TTF
	TTF_Quit();
	//Shut down SDL_Image
	IMG_Quit();
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Renderer* Graphics::getRenderer() const {
	return m_renderer;
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
	this->m_background = background;
}

bool Graphics::isVisible() const {
	return m_visible;
}

void Graphics::setVisible(const bool visible) {
	this->m_visible = visible;
}

SDL_Window* Graphics::getWindow() const {
	return m_window;
}

SDL_Surface* Graphics::getScreenSurface() const {
	return m_screenSurface;
}
