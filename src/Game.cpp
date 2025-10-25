#include "Game.h"

// if you get the error 'The code execution cannot proceed because xxx.dll was not found.'
// check if its linked in your path variables

// TODO: 
// 1. change main to have game states: menu and game
// 2. proper file saving and loading, save script file used, cur background, sprites, and text line
// 3. music
// 3. basic music commands: start, stop, pause, volume
// 3. sound effects

// ensure every system can properly load before we run the game, if we run into errors
// we want to exit early
bool Game::Init() {
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
	// if we reach the end of the init, we can proceed with 
	// starting the game

	// LOAD GLOBALS (there has to be a better way to do this?
	spriteManager.setRenderer(gRenderer);
	spriteManager.setSpriteTexPath(GLOBAL_SPRITES_PATH);

	textManager.setRenderer(gRenderer);
	textManager.setFont(GLOBAL_FONT_PATH);

	uiManager.setRenderer(gRenderer);

	gBackground.setRenderer(gRenderer);

	/// REMOVE LATER
	gBlackBox = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (!interpreter.OpenScript(GLOBAL_SCRIPTS_PATH + script_name)) { return false; }

	return true;
}

void Game::Quit() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

// run is called from main, checks for event quit
// run handles update and render as seperate methods to call

void Game::Run() {
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) {
		running = false;
		return; // return early as its time to exit
	}

	
	// calculate deltatime
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	LAST = NOW;

	Update(e, deltaTime);
	Render();
}

void Game::Update(SDL_Event e, double deltaTime) {
	// place logic here

	interpreter.Run(e, deltaTime, spriteManager, textManager, uiManager, gBackground);

	for (Button* b : uiManager.GetUiVector()) {
		b->Update(e);
	}
}

void Game::Render() {
	// need to turn this into properly layered rendering
	// right now we can do things like hide specific layers
	// which we want to do in certain events (ie show CG background)
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	// layer -1 background
	gBackground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// layer 1 character sprites
	for (Sprite* s : spriteManager.getSpriteVector()) {
		// change render to be scaled based from settings
		s->render(s->getX(), s->getY(), s->getWidth() / 1.5, s->getHeight() / 1.5);
	}

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);
	SDL_RenderFillRect(gRenderer, &gBlackBox);

	// layer 2 text
	int index = 0;
	for (Text* t : textManager.getTextVector()) {
		if (t->curTextLen == 0) { continue; }
		t->textTexture->loadFromRenderedText(t->text.substr(0, t->curTextLen), t->textColor);
		t->textTexture->render(tOffsetX, (tOffsetY * index) + tOffsetX);
		index++;
	}

	// layer 3 buttons/ui?
	for (Button* b : uiManager.GetUiVector()) {
		b->render(b->getX(), b->getY());
		b->showText();
	}

	SDL_RenderPresent(gRenderer);
}



