//
// Created by Viktor on 21.12.2020 г..
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../../geometry/include/matrix4.h"
#include "../../geometry/include/vector3.h"
#include "frustum.h"

/**
 *  @pdf https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjz_Y71-t7tAhVCPuwKHVgYCCoQFjACegQIARAC&url=https%3A%2F%2Fweb.cs.wpi.edu%2F~emmanuel%2Fcourses%2Fcs543%2Ff13%2Fslides%2Flecture04_p3.pdf&usg=AOvVaw3DhRKP2d1wamu2osZL4Ibp
 *  @link https://en.wikipedia.org/wiki/Viewing_frustum
 */

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
