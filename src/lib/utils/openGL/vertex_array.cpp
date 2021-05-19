//
// Created by Viktor on 17.2.2021 г..
//

#include "include/vertex_array.h"

#include <algorithm>

#include "include/lib.h"


VertexArray::VertexArray() {
	arrayObject = 0;
	glGenVertexArrays(1, &arrayObject);
}

VertexArray::VertexArray(VertexArray&& other) noexcept : arrayObject(other.arrayObject){
	other.arrayObject = 0;
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &arrayObject);
	arrayObject = 0;
	unbind();
}

void VertexArray::bind() const {
	glBindVertexArray(arrayObject);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}
