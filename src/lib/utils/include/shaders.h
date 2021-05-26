//
// Created by Viktor on 27.12.2020 г..
//

#ifndef SHADERS_H
#define SHADERS_H

#if !defined(__EMSCRIPTEN__)
#include "GL/glew.h"
#else
#include <GLES3/gl3.h>
#endif
#include "../geometry/include/matrix4.h"
#include "../geometry/include/vector2.h"
#include <unordered_map>
#include <fstream>

static const std::string shadersPath = "src/assets/shaders/";

class Shaders {
private:
	const char* vertexShader;
	const char* fragShader;
	const char* geomShader;
	unsigned int vertexShaderID;
	unsigned int fragShaderID;
	unsigned int geomShaderID;
	unsigned int shaderProgram;
	std::unordered_map<std::string, GLint> uniforms;
	void checkForCompileError(unsigned int type);
public:
	Shaders(const std::string& vertexShader, const std::string& fragShader);
	Shaders(const std::string& vertexShader, const std::string& fragShader, const std::string& geomShader);
	~Shaders();
	std::string readFromFile(const std::string& path);
	void compile();


	void begin();
	void end();
	unsigned int getProgram();

	GLint getUniformLocation(std::string& name);
	void setMatrix4(std::string name, const Matrix4f& mat);
	void setInt(std::string name, int number);
	void setVector3f(std::string name, float x, float y, float z);
	void setVector3f(std::string name, const Vector3f& vec);
};


#endif //SHADERS_H
