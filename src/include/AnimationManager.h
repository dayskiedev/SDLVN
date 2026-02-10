#pragma once

// Animation manager for all game related animations
// animations are stored into a queue  that every deltatime update
// increments each current animation by whatever value it needs to update too
// when an animation is finished the reference is removed from the queue

// maybe have some sort of animation running check to wait for when an animation is finished?

// need to add
// - animation queue
// - actual animations (fade in/out, shake, etc)
// - play animation function
// - will be managed as usual by gamemanager
// - could be extendeed to animate ui features as well? (menu fade ins, etc?)

#include "Sprite.h"

class AnimationManager {
	void PlayAnimation(Sprite& sprite, std::string animationToPlay, double speed);
};