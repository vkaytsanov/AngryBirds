//
// Created by Viktor on 6.1.2021 г..
//

#include "include/first_person_camera_controller.h"
#include "../../include/lib.h"

FirstPersonCameraController::FirstPersonCameraController(Camera* camera) {
	m_pCamera = camera;
}

void FirstPersonCameraController::handleButtonMovement(const float dt) {
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;

	if (Lib::input->isKeyPressed(SDLK_a)) {
		horizontalInput -= (dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_d)) {
		horizontalInput += (dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_w)) {
		verticalInput -= (dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_s)) {
		verticalInput += (dt * CHARACTER_MOVEMENT_INTENSITY);
	}

	if (horizontalInput != 0.0f || verticalInput != 0.0f) {
		m_pCamera->m_pTransform->translate(m_pCamera->m_pTransform->forward * verticalInput +
		                                   m_pCamera->m_pTransform->right * horizontalInput);
	}
}

void FirstPersonCameraController::handleMouseMovement(const float dt) {
	if (!firstTime) {
		float xRot = -(Lib::input->getMouseDeltaY()) * dt * CAMERA_MOVEMENT_INTENSITY;
		float yRot = (Lib::input->getMouseDeltaX()) * dt * CAMERA_MOVEMENT_INTENSITY;
		m_pCamera->m_pTransform->rotateClampX(Vector3f(xRot, yRot, 0), 90.0f);
	}
	else {
		firstTime = false;
	}
	Lib::input->resetMouse();

}

void FirstPersonCameraController::update(const float dt) {
	handleButtonMovement(dt);
	if (Lib::input->isKeyPressed(SDLK_ESCAPE)) {
		shouldMouseMove = !shouldMouseMove;
	}
	if (!shouldMouseMove) return;
	handleMouseMovement(dt);
}

