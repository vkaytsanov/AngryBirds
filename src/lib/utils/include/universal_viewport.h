//
// Created by Viktor on 20.12.2020 г..
//

#ifndef UNIVERSAL_VIEWPORT_H
#define UNIVERSAL_VIEWPORT_H


#include "viewport.h"
#include <cmath>

/** Viewport that remains the aspect ratio and its dimensions can't be
 * lesser than the specified in @param minWorldWidth and @param minWorldHeight */
class UniversalViewport : public Viewport {
private:
	float m_minWorldWidth;
	float m_minWorldHeight;
public:
	UniversalViewport(float minWorldWidth, float minWorldHeight);
	UniversalViewport(float minWorldWidth, float minWorldHeight, Camera* camera);
	void update(int screenWidth, int screenHeight, bool centerCamera) override;
	float getMinWorldWidth() const;
	void setMinWorldWidth(float minWorldWidth);
	float getMinWorldHeight() const;
	void setMinWorldHeight(float minWorldHeight);
};


#endif //UNIVERSAL_VIEWPORT_H
