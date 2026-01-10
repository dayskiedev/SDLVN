#include "AudioManager.h"

// gets initalised first.
AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
	Mix_FreeChunk(btnHover);
	Mix_FreeChunk(btnClick);
	Mix_FreeChunk(tempSFXChunk);
	Mix_HaltMusic();

	btnHover = NULL;
	btnClick = NULL;
	tempSFXChunk = NULL;
	curSong = NULL;
}

void AudioManager::LoadSystemSounds() {
	// loading sounds that will be commonly used so we don't need to keep reloading them
	btnHover = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_hover.wav").c_str());
	btnClick = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + "snd_click.wav").c_str());

	soundMap["btn_click"] = btnClick;
	soundMap["btn_hover"] = btnHover;

	std::cout << "System Sounds Loaded" << std::endl;
}

void AudioManager::PlaySound(std::string sound) {
	tempSFXChunk = soundMap[sound];
	
	// any sound that is played is added to this cache so we dont constantly have to reload it
	// even ones that may only play once though. However most games do not have that many sounds for this to be an issue.
	if (tempSFXChunk == NULL) {
		std::cout << "Unable to find sound " << sound << " in cache, loading sound..." << std::endl;
		tempSFXChunk = Mix_LoadWAV((GLOBAL_SOUNDS_PATH + sound).c_str());
		soundMap[sound] = tempSFXChunk;
;	}

	Mix_PlayChannel(-1, tempSFXChunk, 0);
}

void AudioManager::PlaySong(std::string song) {
	// in this case we dont need to worry about caching the song as there will only ever be 
	// If a song is paused and you then play a new song, the current song will be replaced with
	// this new song and will automatically unpause.
	curSong = Mix_LoadMUS(song.c_str());
	if (curSong == NULL) {
		std::cout << "Error loading song " << song << std::endl;
		return;
	}
	Mix_PlayMusic(curSong, -1);
}

void AudioManager::PauseSong() {
	Mix_PauseMusic();
}

void AudioManager::StopSong() {
	Mix_HaltMusic();
	curSong = NULL;
}

void AudioManager::ResumeSong() {
	Mix_ResumeMusic();
}