//
// Created by Viktor on 21.12.2020 г..
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../../geometry/include/matrix4.h"
#include "../../geometry/include/vector3.h"
#include "frustum.h"

// if (0, 0) should be in the middle of the screen
#define ORIGIN_IS_MIDDLE
// if (0, 0) should be in the bottom-left of the screen
// #define ORIGIN_IS_BOTTOM_LEFT

class Camera {
protected:
	/** near clipping plane */
	float m_nearPlane = 0.001f;
	/** far clipping plane */
	float m_farPlane = 100.0f;
	/** Camera m_projection matrix */
	Matrix4f m_projection;
	/** Camera's m_combined matrix */
	Matrix4f m_combined;
public:
	Transform* m_pTransform;
	Frustum m_frustum;

	float m_viewportWidth;
	float m_viewportHeight;

	Camera();
	virtual ~Camera() = default;
	virtual void update(bool updateFrustum = true) = 0;
	Matrix4f& getTransformMatrix() const;
	Matrix4f& getProjectionMatrix();
	Matrix4f& getCombinedMatrix();

};


#endif //CAMERA_H
