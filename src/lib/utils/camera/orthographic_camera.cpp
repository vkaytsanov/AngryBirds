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
	update(true);
}

void OrthographicCamera::update(bool updateFrustum) {
	Lib::app->error("OrthographicCamera", "Using not implemented function");
//	m_projection.setToOrthogonal(
//			-m_viewportWidth / 2,
//			m_viewportWidth / 2,
//			-m_viewportHeight / 2,
//			m_viewportHeight / 2,
//			m_nearPlane,
//			m_farPlane
//	);
//	m_view.setToLookAt(position, m_direction, m_up);
//	m_combined = m_projection * m_view;
//
//	if (updateFrustum){
//		m_frustum.update(&m_combined);
//	}
}


