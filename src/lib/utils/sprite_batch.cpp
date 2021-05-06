//
// Created by Viktor on 19.12.2020 г..
//

#include "include/sprite_batch.h"
#include "../include/lib.h"

SpriteBatch::SpriteBatch() {
	drawing = false;
	shaders = nullptr;
}

void SpriteBatch::setupMatrices(const Vector3f& pos) {
	combined = (projection * transform);
	shaders->setMatrix4("proj", combined * Matrix4f().setForTranslation(pos));
	shaders->setInt("tex_id", 0);
}

void SpriteBatch::setupShaders(Shaders* shaders) {
	if (this->shaders != shaders) {
		this->shaders = shaders;
	}
}

void SpriteBatch::begin() {
	if (drawing) return;
	drawing = true;
}


//void SpriteBatch::draw(Cube* cube, Vector3f p_position) {
//	setupShaders(cube->getShaders());
//	shaders->begin();
//	setupMatrices(p_position);
//	cube->draw();
//	shaders->end();
//}

void SpriteBatch::draw(Shaders* shaders) {
	this->shaders = shaders;
	combined = (projection * transform);
	unsigned int matrixID = glGetUniformLocation(shaders->getProgram(), "proj");

	if (matrixID == -1) {
		Lib::app->error("uniforms", "invalid location");
	}
	else {
		Matrix4f mat = combined;
		glUniformMatrix4fv(matrixID, 1, false, mat.a);
	}

}

void SpriteBatch::end() {
	if (!drawing) return;
	drawing = false;
}

void SpriteBatch::setProjectionMatrix(const Matrix4f& mat) {
	projection = mat;
}

void SpriteBatch::setTransformMatrix(const Matrix4f& mat) {
	transform = mat;
}

SpriteBatch::~SpriteBatch() {
	delete shaders;
}










