//
// Created by Viktor on 21.12.2020 г..
//

#include "include/camera.h"

Camera::Camera() {
	m_pTransform = nullptr;
	m_viewportWidth = 0;
	m_viewportHeight = 0;
}


Matrix4f& Camera::getTransformMatrix() const{
	return m_pTransform->transformMatrix;
}

Matrix4f& Camera::getProjectionMatrix() {
	return m_projection;
}

Matrix4f& Camera::getCombinedMatrix() {
	return m_combined;
}
