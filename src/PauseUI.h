#include <iostream>

#include "Config.h"

#ifndef PAUSE_UI
#define PAUSE_UI

#include "GameState.h"
#include "GameManager.h"

// UI Sub-States

class PauseUI : public GameState{
public:
	void EnterState(SDL_Renderer* renderer, GameManager* gameManager);
	void Update(SDL_Event e, double deltaTime);
	void Render();
	void ExitState();
private:
	enum pause_states {
		PAUSE,
		SAVE,
		LOAD,
	};

	SDL_Renderer* pauseRenderer;
};

#endif