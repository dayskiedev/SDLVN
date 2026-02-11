#include "AnimationManager.h"

void AnimationManager::QueueAnimation(std::shared_ptr<Sprite> sprite, std::string animationToPlay, double time, bool waitForAnimation) {
	AnimationData tempData;

	tempData.animationToPlay = animationToPlay;
	tempData._sprite = sprite;
	tempData.waitForAnimation = waitForAnimation;

	// value we use will now depend on the animation we select
	// ie if we select a move one, we need move values
	// lets ignore that for now....

	tempData.curValue = sprite->getAlpha();
}

void AnimationManager::Update(double deltaTime) {

}

// animation queue?

// add to a queue
// have an animation update thats running all the time (?)
// inside this check the vector
// for each element in the vector, update each one by one	
// when an animation is complete, remove it from the queue 

// vector of structs?

// AnimationStruct
// ObjToModify/Animate
// multiplier
// cur value
// animation

// how do we track the current animations progress?
// say i want to fade in, i start with opacity at 0 then it needs to go to 100 over n time

// linear
// m = n/t for out multiplier
// then as we update by deltatime we do m + deltatime to update linearly each frame,
// once this equals n, we have finished the value

// then we could have other animations using other modifiers?