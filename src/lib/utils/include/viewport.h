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
#include "utils/geometry/include/vector2.h"

class Viewport {
private:
	Camera* m_pCamera = nullptr;
protected:
	void setScreenBounds(int x, int y, const int width, const int height);
public:
	static float m_worldWidth;
	static float m_worldHeight;
	static int m_screenX;
	static int m_screenY;
	static int m_screenWidth;
	static int m_screenHeight;
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
	static Vector2i fromScreenToViewport(const Vector2i& pos);
	static Vector2i fromScreenToWindowedViewport(const Vector2i& windowPos, const Vector2i& windowSize, Vector2i pos);
	
};


#endif //VIEWPORT_H
