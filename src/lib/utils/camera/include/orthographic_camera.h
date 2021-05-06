//
// Created by Viktor on 21.12.2020 г..
//

#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H


#include "camera.h"

class OrthographicCamera : public Camera {
public:
	OrthographicCamera();
	OrthographicCamera(float viewportWidth, float viewportHeight);
	void update(bool updateFrustum) override;
};


#endif //ORTHOGRAPHIC_CAMERA_H
