//
// Created by Viktor on 15.1.2021 г..
//

#include "include/animation.h"


Animation::Animation(const std::vector<float>& frameDuration, std::vector<Sprite>&& frames, bool looping) :
	m_frames(std::move(frames)),
	m_frameDuration(frameDuration),
	m_looping(looping) {

}

Animation::Animation(float frameDuration, std::vector<Sprite>&& frames, bool looping) :
	m_frames(std::move(frames)),
	m_looping(looping) {

	m_frameDuration.reserve(m_frames.size());
	for (unsigned i = 0; i < m_frames.size(); i++) {
		m_frameDuration.emplace_back(frameDuration);
	}
}

Animation::~Animation() {
	// for(int i = 0; i < m_frames.size(); i++) {
	// 	m_frames[i].getVao()->free();
	// }
}

void Animation::loadFrames(const float frameDuration, std::vector<Sprite>&& frames, bool looping) {
	m_frameDuration.reserve(frames.size());
	for (unsigned i = 0; i < frames.size(); i++) {
		m_frameDuration.emplace_back(frameDuration);
	}
	this->m_frames = std::move(frames);
	this->m_looping = looping;
}

void Animation::loadFrames(const std::vector<float>& frameDuration, std::vector<Sprite>&& frames, bool looping) {
	this->m_frameDuration = frameDuration;
	this->m_frames = std::move(frames);
	this->m_looping = looping;
}

void Animation::update(float dt) {
	m_currentTime += dt;
}

void Animation::resetTime() {
	m_currentTime = 0;
}

void Animation::reset() {
	m_currentTime = 0;
	m_currentFrame = 0;
}

bool Animation::isFinished() const {
	return m_currentFrame == m_frames.size() - 1 && m_currentTime > m_frameDuration[m_currentFrame];
}

Sprite& Animation::getFrame() {
	if (m_looping) {
		if (m_currentTime > m_frameDuration[m_currentFrame]) {
			m_currentFrame = (m_currentFrame + 1) % m_frames.size();
			m_currentTime = 0.0f;
		}
	}
	else {
		if (m_currentTime > m_frameDuration[m_currentFrame]) {
			m_currentFrame = std::min(m_frames.size() - 1, m_currentFrame + 1);
		}
	}

	return m_frames[m_currentFrame];
}
