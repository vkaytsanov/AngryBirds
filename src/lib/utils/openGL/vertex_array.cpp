//
// Created by Viktor on 17.2.2021 г..
//

#include "include/vertex_array.h"

#include <iostream>


VertexArray::VertexArray(bool isRaii) : m_isRaii(isRaii) {
	if (isRaii) {
		initialize();
	}
}

VertexArray::VertexArray(VertexArray&& other) noexcept : arrayObject(std::move(other.arrayObject)), m_isRaii(std::move(other.m_isRaii)) {
	other.arrayObject = 0;
}

VertexArray::~VertexArray() {
	if (m_isRaii) {
		free();
	}
}

void VertexArray::initialize() {
#if defined(_DEBUG)
	static int counter = 0;
	counter++;
	std::cout << "VertexArray " << counter << " built.\n";
#endif
	arrayObject = 0;
	glGenVertexArrays(1, &arrayObject);
}

void VertexArray::free() {
#if defined(_DEBUG)
	static int counter = 0;
	counter++;
	std::cout << "VertexArray " << counter << " destroyed.\n";
#endif
	glDeleteVertexArrays(1, &arrayObject);
	unbind();
	arrayObject = 0;
}

void VertexArray::bind() const {
	glBindVertexArray(arrayObject);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}
