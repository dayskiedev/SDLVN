#include "AnimationManager.h"

// TODO: WAIT FOR ANIMATION THING
// SOMETIMES WE WANT AN ANIMATION TO HAPPEN BEFORE SOMETHING ELSE DOES
// EXAMPLE EXITING THE SCENE / CHANGING SPRITE
// WE ALSO WANT TO BE ABLE TO END AN ANIMATION EARLY BY CLICKING

void AnimationManager::QueueAnimation(std::shared_ptr<Sprite> sprite, std::string animationToPlay, double time, bool waitForAnimation) {

	// it was becauase this was a single object, not shared?? figure out why
	std::shared_ptr<AnimationData> tempData = std::make_shared<AnimationData>();

	tempData->animationToPlay = animationToPlay;
	tempData->_sprite = sprite;
	tempData->waitForAnimation = waitForAnimation;

	// bug if we start at 0
	tempData->curValue = sprite->getAlpha();
	tempData->multiplier =  255 / (time * 1000);

	animationQueue.push_back(tempData);
}

void AnimationManager::Update(double deltaTime) {
	for (auto anim : animationQueue) {
		if (anim->animationToPlay == "fadeOut") {
			if (anim->curValue <= 0) {
				anim->_sprite->setAlpha(0);
				continue;
			}

			anim->curValue -= (anim->multiplier * deltaTime);
			anim->_sprite->setAlpha(anim->curValue);
		}
		if (anim->animationToPlay == "fadeIn") {
			if (anim->curValue >= 255) {
				anim->_sprite->setAlpha(255);
				continue;
			}

			anim->curValue += (anim->multiplier * deltaTime);
			anim->_sprite->setAlpha(anim->curValue);
		}
	}
}
