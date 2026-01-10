#pragma once

#include <iostream>
#include <unordered_map>

#include "SDL_mixer.h"
#include "Config.h"

// we want to preload some common sounds that will be used all the time.
// - button hover, button click etc
// we also want to dynamically load some sounds
// music should also be dynamically loaded
// we should be able to play it, pause it, and load it
// volume should be managed by config 

class AudioManager {
public:
	AudioManager();
	~AudioManager();

	void LoadSystemSounds();

	void PlaySound(std::string sound);

	void PlaySong(std::string song);
	void PauseSong();
	void ResumeSong();
	void StopSong();

	void SetMasterVolume(int volume);
	void SerSFXVolume(int volume);
	void SetMusicVolume(int volume);

private:
	Mix_Music* curSong = NULL;

	std::unordered_map<std::string, Mix_Chunk*> soundMap;

	// these will be pre-loaded as they will be used a lot.
	Mix_Chunk* btnHover = NULL;
	Mix_Chunk* btnClick = NULL;
	Mix_Chunk* tempSFXChunk = NULL;
};