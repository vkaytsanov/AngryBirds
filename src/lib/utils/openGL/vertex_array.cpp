//
// Created by Viktor on 17.2.2021 г..
//

#include "include/vertex_array.h"


VertexArray::VertexArray() {
	arrayObject = 0;
	glGenVertexArrays(1, &arrayObject);
}

VertexArray::VertexArray(VertexArray&& other) noexcept : arrayObject(other.arrayObject){
	other.arrayObject = 0;
}

VertexArray::~VertexArray() {
	free();
	arrayObject = 0;
}

void VertexArray::free() const {
	glDeleteVertexArrays(1, &arrayObject);
	unbind();
}

void VertexArray::bind() const {
	glBindVertexArray(arrayObject);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}
