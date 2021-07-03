#include "include/graphics.h"
#include "../../src/core/data/include/config_development.h"

IGraphics::IGraphics() : IGraphics(new Configuration()) {
}

IGraphics::IGraphics(Configuration* config) : m_pConfig(config),
                                            m_background(false),
                                            m_visible(true) {
}

void IGraphics::updateTime() {
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

int IGraphics::getWidth() const {
	return m_pConfig->width;
}

int IGraphics::getHeight() const {
	return m_pConfig->height;
}

float IGraphics::getDeltaTime() const {
	return m_deltaTime;
}

float IGraphics::getFps() const {
	return m_fps;
}


void IGraphics::setWidth(const int width) const {
	m_pConfig->width = width;
}

void IGraphics::setHeight(const int height) const {
	m_pConfig->height = height;
}

bool IGraphics::isBackground() const {
	return m_background;
}

void IGraphics::setBackground(const bool background) {
	m_background = background;
}

bool IGraphics::isVisible() const {
	return m_visible;
}

void IGraphics::setVisible(const bool visible) {
	m_visible = visible;
}
