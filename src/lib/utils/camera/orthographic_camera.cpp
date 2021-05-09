//
// Created by Viktor on 21.12.2020 г..
//


#include "include/orthographic_camera.h"
#include "../../include/lib.h"

OrthographicCamera::OrthographicCamera() : OrthographicCamera(Lib::graphics->getWidth(),
                                                              Lib::graphics->getHeight()){
}

OrthographicCamera::OrthographicCamera(const float viewportWidth, const float viewportHeight) {
	this->m_viewportWidth = viewportWidth;
	this->m_viewportHeight = viewportHeight;
	m_nearPlane = 0;

}

void OrthographicCamera::update(bool updateFrustum) {
	// Lib::app->error("OrthographicCamera", "Using not implemented function");
	m_projection.setToOrthogonal(
			-m_viewportWidth / 2,
			m_viewportWidth / 2,
			-m_viewportHeight / 2,
			m_viewportHeight / 2,
			m_nearPlane,
			m_farPlane
	);
	
	m_combined = m_projection * m_pTransform->transformMatrix;

	if (updateFrustum){
		m_frustum.update(&m_combined);
	}
}


