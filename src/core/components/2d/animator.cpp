#include "include/animator.h"

Animator::Animator(std::vector<Animation>& animations) : animations(animations) {
}

Animator::Animator(std::vector<Animation>&& animations) : animations(std::move(animations)) {
}

Sprite& Animator::getFrame() {
	return animations[currentAnimation].getFrame();
}
