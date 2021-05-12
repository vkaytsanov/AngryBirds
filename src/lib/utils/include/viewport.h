//
// Created by Viktor on 20.12.2020 г..
//

#ifndef VIEWPORT_H
#define VIEWPORT_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "../camera/include/camera.h"

class Viewport {
private:
	Camera* m_pCamera = nullptr;
	float m_worldWidth = 0;
	float m_worldHeight = 0;
	int m_screenX = 0;
	int m_screenY = 0;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
protected:
	void setScreenBounds(int x, int y, const int width, const int height);
public:
	Viewport() = default;
	Viewport(Camera* camera);
	virtual ~Viewport() = default;
	virtual void update(int screenWidth, int screenHeight, bool centerCamera) = 0;
	void apply(bool centerCamera) const;
	void setCamera(Camera* camera);
	void setWorldWidth(float worldWidth);
	void setWorldHeight(float worldHeight);
	void setWorldSize(float worldWidth, float worldHeight);
	Camera* getCamera() const;
	float getWorldWidth() const;
	float getWorldHeight() const;
};


#endif //VIEWPORT_H
