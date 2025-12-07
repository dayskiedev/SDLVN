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
		MAIN_PAUSE,
		SAVE,
		LOAD,
		OPTIONS,
	};

	SDL_Renderer* pauseRenderer;
	GameManager* _gameManager;
	std::vector<std::shared_ptr<Button>> testUI;
};

#endif