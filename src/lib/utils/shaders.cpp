//
// Created by Viktor on 27.12.2020 г..
//

#include <string>
#include <sstream>
#include "include/shaders.h"
#include "../include/lib.h"
#include "../../src/core/data/include/config_development.h"


Shaders::Shaders(const std::string& vertexShaderPath, const std::string& fragShaderPath) {
	std::cout << shadersPath + vertexShaderPath << "\n";
#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN_DEVELOPMENT)
	const std::string subFolder = "emscripten/";
#else
	const std::string subFolder = "core/";
#endif

	std::string parsedVertexShader = readFromFile(shadersPath + subFolder + vertexShaderPath);
	vertexShader = parsedVertexShader.c_str();

	std::string parsedFragmentShader = readFromFile(shadersPath + subFolder + fragShaderPath);
	fragShader = parsedFragmentShader.c_str();

	geomShader = nullptr;
	compile();

}

Shaders::Shaders(const std::string& vertexShaderPath, const std::string& fragShaderPath,
                 const std::string& geomShaderPath) {
	std::string parsedVertexShader = readFromFile(shadersPath + vertexShaderPath);
	vertexShader = parsedVertexShader.c_str();

	std::string parsedFragmentShader = readFromFile(shadersPath + fragShaderPath);
	fragShader = parsedFragmentShader.c_str();

	std::string parsedGeometryShader = readFromFile(shadersPath + geomShaderPath);
	geomShader = parsedGeometryShader.c_str();

	compile();
}


std::string Shaders::readFromFile(const std::string& path) {
	std::ifstream stream(path);
	std::string line;
	std::stringstream ss;
	while (std::getline(stream, line)) {
		ss << line << "\n";
	}

	stream.close();

	return ss.str();
}

void Shaders::compile() {
#if defined(__EMSCRIPTEN__)
	Lib::app->log("Shaders", "compiling...");
	std::cout << vertexShader << "\n";
	GLboolean canCompile = false;
	glGetBooleanv(GL_SHADER_COMPILER, &canCompile);
	

	if(!canCompile) {
		Lib::app->error("Shaders", "Can't compile");
		std::cout << "GL Error:" << glGetError() << "\n";
		exit(-1);
	}
#endif
	if (vertexShader == nullptr) {
		Lib::app->error("Shaders", "VertexShader is null");
		exit(-1);
	}
	if (fragShader == nullptr) {
		Lib::app->error("Shaders", "FragShader is null");
		exit(-1);
	}

	Lib::app->log("Shaders", "Trying to Create VertexShader");
	// compiling first the vertex shader
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	Lib::app->log("Shaders", "Trying to get ShaderSource");
	glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
	Lib::app->log("Shaders", "Trying to Compile VertexShader");
	glCompileShader(vertexShaderID);

	checkForCompileError(vertexShaderID);
	Lib::app->log("Shaders", "VertexShader Compiled");
	// compiling now the fragment shader
	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragShader, nullptr);
	glCompileShader(fragShaderID);

	checkForCompileError(fragShaderID);
	Lib::app->log("Shaders", "FragmentShader Compiled");
	// if there is geometry shader
#if !defined(__EMSCRIPTEN__)
	if (geomShader) {
		geomShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geomShaderID, 1, &geomShader, nullptr);
		glCompileShader(geomShaderID);
		checkForCompileError(geomShaderID);
	}
#endif
	shaderProgram = glCreateProgram();
	Lib::app->log("Shaders", "Created Program");
	glAttachShader(shaderProgram, vertexShaderID);
	Lib::app->log("Shaders", "VertexShader Attached");
	glAttachShader(shaderProgram, fragShaderID);
	Lib::app->log("Shaders", "FragmentShader Attached");
	if (geomShader) {
		glAttachShader(shaderProgram, geomShaderID);
	}

	glLinkProgram(shaderProgram);
	Lib::app->log("Shaders", "Shaders Linked");
	int status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		int logLength = 0;
		char message[1024];
		glGetProgramInfoLog(shaderProgram, 1024, &logLength, message);
		// Write the error to a log
		Lib::app->error("The shader", fragShader);
		Lib::app->error("LinkingShaderProgramError", message);

		exit(-1);
	}
	else {
		Lib::app->log("LinkingShaderProgram", "successful");
	}

}


void Shaders::checkForCompileError(unsigned int type) {
	int status;
	glGetShaderiv(type, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		int logLength = 0;
		char message[1024];
		glGetShaderInfoLog(type, 1024, &logLength, message);
		// Write the error to a log
		Lib::app->error("ShaderError", message);
	}
	else {
		Lib::app->log("Shader", "compiled successfully");
	}
}

void Shaders::begin() {
	glUseProgram(shaderProgram);
}

void Shaders::end() {
	glUseProgram(0);
}

Shaders::~Shaders() {
	glUseProgram(0);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);
	glDeleteProgram(shaderProgram);
}

unsigned int Shaders::getProgram() {
	return shaderProgram;
}

GLint Shaders::getUniformLocation(std::string& name) {
	if (uniforms.find(name) == uniforms.end()) {
		int res = glGetUniformLocation(shaderProgram, name.c_str());
		if (res == -1) {
			Lib::app->error("uniforms", ("invalid location on " + name).c_str());
			exit(-1);
		}
		uniforms[name] = res;
	}


	return uniforms[name];
}

void Shaders::setMatrix4(std::string name, const Matrix4f& mat) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, mat.a);
}

void Shaders::setInt(std::string name, const int number) {
	glUniform1i(getUniformLocation(name), number);
}


void Shaders::setVector3f(std::string name, float x, float y, float z) {
	glUniform3f(getUniformLocation(name), x, y, z);
}

void Shaders::setVector3f(std::string name, const Vector3f& vec) {
	setVector3f(name, vec.x, vec.y, vec.z);
}
