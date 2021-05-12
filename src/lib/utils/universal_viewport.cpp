//
// Created by Viktor on 20.12.2020 г..
//

#include "../include/lib.h"
#include "include/universal_viewport.h"
#include "camera/include/orthographic_camera.h"

UniversalViewport::UniversalViewport(const float minWorldWidth, const float minWorldHeight)
	: UniversalViewport(minWorldWidth, minWorldHeight, new OrthographicCamera()) {
}


UniversalViewport::UniversalViewport(float minWorldWidth, float minWorldHeight, Camera* camera) :
	m_minWorldWidth(minWorldWidth),
	m_minWorldHeight(minWorldHeight),
	Viewport(camera) {

}

float UniversalViewport::getMinWorldWidth() const {
	return m_minWorldWidth;
}

void UniversalViewport::setMinWorldWidth(float minWorldWidth) {
	m_minWorldWidth = minWorldWidth;
}

float UniversalViewport::getMinWorldHeight() const {
	return m_minWorldHeight;
}

void UniversalViewport::setMinWorldHeight(float minWorldHeight) {
	m_minWorldHeight = minWorldHeight;
}


void UniversalViewport::update(int screenWidth, int screenHeight, bool centerCamera) {
	float worldWidth = m_minWorldWidth;
	float worldHeight = m_minWorldHeight;

	const float screenRatio = (float)screenHeight / (float)screenWidth;
	const float worldRatio = worldHeight / worldWidth;
	const float scale =
		screenRatio > worldRatio ? (float)screenWidth / m_minWorldWidth : (float)screenHeight / m_minWorldHeight;

	int viewportWidth = (int)std::round(worldWidth * scale);
	int viewportHeight = (int)std::round(worldHeight * scale);

	// Enlarging the m_pViewport by its short side
	if (viewportWidth < screenWidth) {
		float toViewportSpace = (float)viewportHeight / worldHeight;
		float toWorldSpace = worldHeight / (float)viewportHeight;
		float lengthen = (float)(screenWidth - viewportWidth) * toWorldSpace;
		worldWidth += lengthen;
		viewportWidth += (int)(lengthen * toViewportSpace);
	}
	else if (viewportHeight < screenHeight) {
		float toViewportSpace = (float)viewportWidth / worldWidth;
		float toWorldSpace = worldWidth / (float)viewportWidth;
		float lengthen = (float)(screenHeight - viewportHeight) * toWorldSpace;
		worldHeight += lengthen;
		viewportHeight += (int)(lengthen * toViewportSpace);
	}

	setWorldSize(worldWidth, worldHeight);
	setScreenBounds((screenWidth - viewportWidth) / 2, (screenHeight - viewportHeight) / 2, viewportWidth,
	                viewportHeight);
	apply(centerCamera);
}
