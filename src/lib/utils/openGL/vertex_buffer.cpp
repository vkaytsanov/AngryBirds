//
// Created by Viktor on 17.2.2021 г..
//

#include "include/vertex_buffer.h"
#include "../../include/lib.h"

VertexBuffer::VertexBuffer() {
	m_buffer = 0;
	glGenBuffers(1, &m_buffer);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_buffer);
	unbind();
}

void VertexBuffer::bufferData(GLsizeiptr size, void* data, GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                       const GLvoid* pointer) {
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::vertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer) {
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, size, type, stride, pointer);
}

void VertexBuffer::bufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data) {
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
