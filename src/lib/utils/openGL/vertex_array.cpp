//
// Created by Viktor on 17.2.2021 г..
//

#include "include/vertex_array.h"

#include <iostream>

VertexArray::VertexArray() {
	arrayObject = 0;
	glGenVertexArrays(1, &arrayObject);
}

VertexArray::VertexArray(const VertexArray& other) : arrayObject(other.arrayObject){
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &arrayObject);
	unbind();
	std::cout << "Vertex Destructor\n";
}

void VertexArray::bind() const {
	glBindVertexArray(arrayObject);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}
