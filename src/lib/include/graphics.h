#ifndef GRAPHICS
#define GRAPHICS


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <string>

#include "configuration.h"


class Graphics {
	friend class Application;
private:
	Configuration* m_pConfig;
	SDL_Window* m_pWindow;
	SDL_GLContext m_pContext;
	SDL_Surface* m_pScreenSurface;
	SDL_Renderer* m_pRenderer;
	uint32_t m_lastTime = 0;
	float m_deltaTime = 0;
	uint16_t m_fps = 0;
	uint16_t m_frames = 0;
	uint64_t m_frameStart = 0;
	bool m_background;
	bool m_visible;
	std::string m_glslVersion;
public:
	explicit Graphics(Configuration* config);
	Graphics();
	~Graphics();
	bool isBackground() const;
	void setBackground(const bool background);
	bool isVisible() const;
	void setVisible(const bool visible);
	void updateTime();
	void setWidth(const int width) const;
	void setHeight(const int height) const;
	int getWidth() const;
	int getHeight() const;
	float getDeltaTime() const;
	float getFps() const;
	void createWindow();
	void update();
	SDL_Renderer* getRenderer() const;
	SDL_Window* getWindow() const;
	SDL_Surface* getScreenSurface() const;
	SDL_GLContext getContext() const;
	const char* getGlslVersion() const;
};

#endif