//
// Created by Viktor on 19.12.2020 г..
//

#ifndef DUCKHUNT_SPRITE_BATCH_H
#define DUCKHUNT_SPRITE_BATCH_H

#include "../geometry/include/matrix4.h"
#include "shaders.h"

class SpriteBatch {
private:
	Matrix4f combined;
	Matrix4f projection;
	Matrix4f transform;
	Shaders* shaders;
	bool drawing;
	void setupMatrices(const Vector3f& pos);
	void setupShaders(Shaders* shaders);
public:
	SpriteBatch();
	~SpriteBatch();
	void setProjectionMatrix(const Matrix4f& mat);
	void setTransformMatrix(const Matrix4f& mat);
	void begin();
	void draw(Shaders* shaders);
	void end();

};


#endif //DUCKHUNT_SPRITE_BATCH_H
