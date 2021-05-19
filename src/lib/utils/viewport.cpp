//
// Created by Viktor on 20.12.2020 г..
//
#include "GL/glew.h"
#include <cmath>
#include "include/viewport.h"

float Viewport::m_worldWidth;
float Viewport::m_worldHeight;
int   Viewport::m_screenX;
int	  Viewport::m_screenY;
int   Viewport::m_screenWidth;
int   Viewport::m_screenHeight;

Viewport::Viewport(Camera* camera) : m_pCamera(camera) {
}

void Viewport::apply(bool centerCamera) const {
	glViewport(m_screenX, m_screenY, m_screenWidth, m_screenHeight);
	m_pCamera->m_viewportWidth = m_worldWidth;
	m_pCamera->m_viewportHeight = m_worldHeight;
	if (centerCamera) {
		m_pCamera->m_pTransform->position.x = m_worldWidth / 2;
		m_pCamera->m_pTransform->position.y = m_worldHeight / 2;
		m_pCamera->m_pTransform->position.z = 0;
	}
}

void Viewport::setCamera(Camera* camera) {
	this->m_pCamera = camera;
}

Camera* Viewport::getCamera() const {
	return m_pCamera;
}

float Viewport::getWorldWidth() const {
	return m_worldWidth;
}

void Viewport::setWorldWidth(float worldWidth) {
	m_worldWidth = worldWidth;
}

float Viewport::getWorldHeight() const {
	return m_worldHeight;
}

Vector2i Viewport::fromScreenToViewport(const Vector2i& pos) {
	static float widthRatio = static_cast<float>(m_screenWidth) / m_worldWidth;
	static float heightRatio = static_cast<float>(m_screenHeight) / m_worldHeight;
#if defined(ORIGIN_IS_MIDDLE)
	return Vector2i(static_cast<float>(pos.x) / widthRatio - m_worldWidth / 2,
	                static_cast<float>(pos.y) / heightRatio - m_worldHeight / 2);
#elif defined(ORIGIN_IS_BOTTOM_LEFT)
	Lib::app->error("fromScreenToViewport", "not implemented function");
	return Vector2i();
#endif
}

void Viewport::setWorldHeight(float worldHeight) {
	m_worldHeight = worldHeight;
}

void Viewport::setWorldSize(float worldWidth, float worldHeight) {
	this->m_worldWidth = worldWidth;
	this->m_worldHeight = worldHeight;
}

void Viewport::setScreenBounds(const int x, const int y, const int width, const int height) {
	m_screenX = x;
	m_screenY = y;
	m_screenWidth = width;
	m_screenHeight = height;
}
