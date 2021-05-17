//
// Created by Viktor on 21.12.2020 г..
//


#include "include/orthographic_camera.h"
#include "../../include/lib.h"

OrthographicCamera::OrthographicCamera() : OrthographicCamera(Lib::graphics->getWidth(),
                                                              Lib::graphics->getHeight()){
}

OrthographicCamera::OrthographicCamera(const float viewportWidth, const float viewportHeight) {
	m_viewportWidth = viewportWidth;
	m_viewportHeight = viewportHeight;
	m_nearPlane = 0;

}

void OrthographicCamera::update(bool updateFrustum) {
#if defined(ORIGIN_IS_MIDDLE)
	m_projection.setToOrthogonal(
			-m_viewportWidth / 2,
			m_viewportWidth / 2,
			-m_viewportHeight / 2,
			m_viewportHeight / 2,
			m_nearPlane,
			m_farPlane
	);
#elif defined(ORIGIN_IS_BOTTOM_LEFT)
	m_projection.setToOrthogonal(
			0,
			m_viewportWidth,
			0,
			m_viewportHeight,
			m_nearPlane,
			m_farPlane
	);
#endif
	
	
	m_combined = m_projection * m_pTransform->transformMatrix;

	if (updateFrustum){
		m_frustum.update(&m_combined);
	}
}


