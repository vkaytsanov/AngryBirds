//
// Created by Viktor on 6.1.2021 г..
//

#ifndef FIRST_PERSON_CAMERA_CONTROLLER_H
#define FIRST_PERSON_CAMERA_CONTROLLER_H


#include "camera.h"
#include "../../include/input_processor.h"

class FirstPersonCameraController : public InputProcessor {
private:
	Camera* m_pCamera;
	const float CAMERA_MOVEMENT_INTENSITY = 25.f;
	const float CHARACTER_MOVEMENT_INTENSITY = 7.f;
	bool firstTime = true;
	bool shouldMouseMove = true;
	void handleButtonMovement(const float dt);
	void handleMouseMovement(const float dt);
public:
	explicit FirstPersonCameraController(Camera* camera);
	FirstPersonCameraController() = default;
	void update(const float dt);
};


#endif //FIRST_PERSON_CAMERA_CONTROLLER_H
