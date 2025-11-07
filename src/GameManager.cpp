#include "GameManager.h"

// game manager will initialise the master window that gets sent to both the game and the menu

bool GameManager::Init() {
	//initialze sdl
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL could not be initialized!" << std::endl;
		return false;
	}

	// Create window
	gWindow = SDL_CreateWindow("SDLVN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		std::cout << "Window could not be created!" << std::endl;
		return false;
	}

	// Create Renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(gRenderer, 255, 175, 222, 0xFF);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	// imgs
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_Image could not be initialised! " << IMG_GetError() << std::endl;
		return false;
	}

	// fonts
	if (TTF_Init() == -1) {
		std::cout << "SDL_TTF could not be initialised! " << TTF_GetError() << std::endl;
		return false;
	}

	// audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer could not be initalised! " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

void GameManager::Run() {
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) {
		running = false;
		return; // return early as its time to exit
	}

	// calculate deltatime
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	LAST = NOW;

	// Handle Gamestates
	switch (gameState)
	{
		case GameManager::GAME:
			_game.Init(gRenderer);
			_game.Run(e, deltaTime);
			break;
		case GameManager::MENU:
			std::cout << "Yer in the menu now hehehehe";
			break;
		case GameManager::PAUSE:
			break;
	default:
		break;
	}
}

void GameManager::Quit() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}