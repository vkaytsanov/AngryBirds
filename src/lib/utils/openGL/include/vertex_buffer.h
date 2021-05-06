//
// Created by Viktor on 17.2.2021 г..
//

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "GL/glew.h"

class VertexBuffer {
private:
	unsigned int m_buffer;
public:
	VertexBuffer();
	~VertexBuffer();
	static void bufferData(GLsizeiptr size, void* data, GLenum usage);
	static void bufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);
	static void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
	                                const GLvoid* pointer);
	static void vertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
	void bind() const;
	static void unbind();
};


#endif //VERTEX_BUFFER_H
