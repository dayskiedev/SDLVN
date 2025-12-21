#include "AudioManager.h"

// gets initalised first.
AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
	Mix_FreeChunk(btnHover);
	Mix_FreeChunk(btnClick);
	Mix_FreeChunk(customSound);

	btnHover = NULL;
	btnClick = NULL;
	customSound = NULL;
}

void AudioManager::LoadSystemSounds() {
	// loading sounds that will be commonly used so we don't need to keep reloading them
	btnHover = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_hover.wav").c_str());
	btnClick = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_click.wav").c_str());
	std::cout << "System Sounds Loaded" << std::endl;
}

void AudioManager::PlaySound(std::string sound) {
	Mix_PlayChannel(-1, btnClick, 0);
}