//
// Created by Viktor on 15.1.2021 г..
//

#ifndef ANIMATION_H
#define ANIMATION_H


#include <vector>
#include "../core/components/2d/include/sprite.h"

/** Animation class consists of frames, each representing
 * a sprite, which is 4 vertices and 4 uvs.
 *
 * Frames are changed based on the #m_frameDuration for the corresponding sprite.
 * When the #m_currentTime has passed in value the frame duration, it switches the
 * #m_currentFrame and resets the timer.
 */
class Animation {
private:
	std::vector<Sprite> m_frames;
	std::vector<float> m_frameDuration;
	bool m_looping = false;
	float m_currentTime = 0.0f;
	unsigned m_currentFrame = 0;
public:
	Animation() = default;
	Animation(const std::vector<float>& frameDuration, std::vector<Sprite>&& frames, bool looping = false);
	Animation(float frameDuration, std::vector<Sprite>&& frames, bool looping = false);
	void loadFrames(const float frameDuration, std::vector<Sprite>&& frames, bool looping = false);
	void loadFrames(const std::vector<float>& frameDuration, std::vector<Sprite>&& frames, bool looping = false);
	void update(float dt);
	bool isFinished() const;
	Sprite& getFrame();

	template <typename Archive>
	void save(Archive& archive);

	template <typename Archive>
	void load(Archive& archive);
};

template <typename Archive>
void Animation::save(Archive& archive) {
	// TODO
	archive(m_frames);
	archive(m_frameDuration);
}

template <typename Archive>
void Animation::load(Archive& archive) {
	
}


#endif //ANIMATION_H
