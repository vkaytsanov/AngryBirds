#include <GL/glew.h>
#include "include/frame_buffer.h"
#include "include/lib.h"

FrameBuffer::FrameBuffer() {
	glGenFramebuffers(1, &m_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_buffer);
	glGenTextures(1, &m_textureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Lib::graphics->getWidth(), Lib::graphics->getHeight(), 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureBuffer, 0);

	glGenRenderbuffers(1, &m_renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Lib::graphics->getWidth(), Lib::graphics->getHeight());

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);

	std::cout << "Color buffer: " << m_textureBuffer << std::endl;
	std::cout << "Depth buffer: " << m_renderBuffer << std::endl;
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		exit(-1);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() {
	glDeleteRenderbuffers(1, &m_renderBuffer);
	glDeleteBuffers(1, &m_textureBuffer);
	glDeleteFramebuffers(1, &m_buffer);
}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_buffer);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attach(std::shared_ptr<Texture> texture) {
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getBuffer(), 0);
}

unsigned FrameBuffer::getTextureBuffer() {
	return m_textureBuffer;
}
