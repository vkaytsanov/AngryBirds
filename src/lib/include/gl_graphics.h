#pragma once
#include "include/graphics.h"

class Listener;

class GLGraphics : public IGraphics{
private:
	SDL_Window* m_pWindow;
	SDL_GLContext m_pContext;
	SDL_Surface* m_pScreenSurface;
	SDL_Renderer* m_pRenderer;
	std::string m_glslVersion;
private:
	void initImgui();
public:
	explicit GLGraphics(Configuration* config);
	~GLGraphics() override;
public:
	void initialize() override;
	SDL_Window* getWindow() const;
	SDL_Surface* getScreenSurface() const;
	SDL_GLContext getContext() const;
	const char* getGlslVersion() const;
	void swapBuffers(Listener* listener) override;
};
