#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>

#include <string>

#include "configuration.h"

class Listener;

class IGraphics {
	friend class Application;
private:
	uint32_t m_lastTime = 0;
	float m_deltaTime = 0;
	uint16_t m_fps = 0;
	uint16_t m_frames = 0;
	uint64_t m_frameStart = 0;
	bool m_background;
	bool m_visible;
protected:
	Configuration* m_pConfig;
public:
	explicit IGraphics(Configuration* config);
	IGraphics();
	virtual ~IGraphics() = default;
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
	virtual void initialize() = 0;
	virtual void swapBuffers(Listener* listener) = 0;
};

#endif
