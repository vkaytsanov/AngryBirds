//
// Created by Viktor on 17.2.2021 г..
//

#include "include/index_buffer.h"
#include "../../include/lib.h"

IndexBuffer::IndexBuffer() {
	buffer = 0;
	glGenBuffers(1, &buffer);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &buffer);
	unbind();
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void IndexBuffer::bufferData(GLsizeiptr size, void* data, GLenum usage) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
