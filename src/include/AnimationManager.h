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
#include <vector>

class AnimationManager {
public:
	void QueueAnimation(std::shared_ptr<Sprite> sprite, std::string animationToPlay, double time, bool waitForAnimation);
	void Update(double deltaTime);
private:
	struct AnimationData {
		std::string animationToPlay;
		double curValue;
		double multiplier; 
		std::shared_ptr<Sprite> _sprite;		
		bool waitForAnimation;
	};

	std::vector<AnimationData> animationQueue;
};

