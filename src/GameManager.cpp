#include "GameManager.h"

// game manager will initialise the master window that gets sent to both the game and the menu

bool GameManager::Init() {
	//initialze sdl
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL could not be initialised!" << std::endl;
		return false;
	}
	std::cout << "SDL initialised" << std::endl;

	// Create window
	gWindow = SDL_CreateWindow(PROGRAM_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		std::cout << "Window could not be created!" << std::endl;
		return false;
	}
	std::cout << "Window created" << std::endl;

	// Create Renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "Renderer created" << std::endl;

	SDL_SetRenderDrawColor(gRenderer, 255, 175, 222, 0xFF);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	// imgs
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_Image could not be initialised! " << IMG_GetError() << std::endl;
		return false;
	}
	std::cout << "IMG initialised" << std::endl;

	// fonts
	if (TTF_Init() == -1) {
		std::cout << "SDL_TTF could not be initialised! " << TTF_GetError() << std::endl;
		return false;
	}
	std::cout << "TTF initialised" << std::endl;

	// audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer could not be initalised! " << Mix_GetError() << std::endl;
		return false;
	}

	Mix_Volume(2, 30);
	std::cout << "Mixer initialised" << std::endl;

	// start off by setting the launch state a menu instance
	currentState = std::make_unique<Menu>();
	currentState->EnterState(gRenderer, this);

	std::cout << "Default state initialised" << std::endl;

	saveManager = std::make_unique<SaveManager>();

	std::cout << "Save Manager initialised" << std::endl;


	//
	//SCREEN_WIDTH = 1920;
	//SCREEN_HEIGHT = 1080;
	//SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	//SDL_SetWindowFullscreen(gWindow, true);
	//SDL_SetWindowBordered(gWindow, SDL_FALSE);
	
	return true;
}

void GameManager::Run() {

	// create and have a master audiomanager running to play all music / sounds

	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) {
		running = false;
		return; // return early as its time to exit
	}

	// calculate deltatime
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	LAST = NOW;

	currentState->Update(e, deltaTime);
	currentState->Render();

	// if we called a change of state, wait until all updates/renders have occurred, then change
	// state so that no chance of objects in state trying to get things that have been deleted..
	if (pendingState) {
		currentState->ExitState();
		currentState = std::move(pendingState);
		// because we move ownership to currentState, pending state
		// auto gets made a nullptr, so we wont have an infinite loop when changing states
		currentState->EnterState(gRenderer, this);
	}

}   

void GameManager::RequestState(std::unique_ptr<GameState> state) {
	// transfer ownership of this state to pending state
	pendingState = std::move(state);
}

void GameManager::Quit() {
	currentState = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

bool GameManager::SaveExists(std::string savePath) {
	return saveManager->SaveExists(savePath);
}

void GameManager::SetSaveReferences(std::shared_ptr<Interpreter> interpreterInfo, std::shared_ptr<SpriteManager> spriteManagerInfo, std::shared_ptr<Sprite> background) {
	_interpreterInfo = interpreterInfo;
	_spriteManagerInfo = spriteManagerInfo;
	_background = background;
}

void GameManager::QuickSave() {
	// this directly sets the gamemangers savedata and currently just runs whenever we pause,
	// so the game knows where to go back to afterwards....
	// ideally id like to instead just renderer directly in the game but idk...
	saveData.scriptPath = _interpreterInfo->GetCurrentScript();
	saveData.scriptLine = _interpreterInfo->GetCurrentScriptLine();
	saveData.backgroundPath = _background->GetSpriteTexPath();
	std::vector<SpriteInformation> spriteInfoRaw;
	for (auto s : _spriteManagerInfo->GetSprites()) {
		SpriteInformation sInfo;

		sInfo.spriteName = s->GetSpriteName();
		sInfo.spriteLocation = s->GetSpriteTexPath();
		sInfo.w = s->getWidth();
		sInfo.h = s->getHeight();
		sInfo.x = s->getX();
		sInfo.y = s->getY();

		spriteInfoRaw.push_back(sInfo);
	}
	saveData.sprites = spriteInfoRaw;
}

void GameManager::SaveGame(std::string savePath) {
	// here we just perfrom the quick save but we want to pass it through to the save manager
	// in order to actually write the data into binary

	QuickSave();
	saveManager->Save(saveData);
}

void GameManager::LoadSave(std::string savePath) {
	// this will set the GameManagers saveStruct which will be used by the interpretor
	if (!SaveExists(savePath)) {
		std::cout << "Unable to find save: " << savePath << std::endl;
		return;
	}


	if (!saveManager->Load(saveData, savePath)) {
		std::cout << "error loading save";
	}

	RequestState(std::make_unique<Game>());
}

void GameManager::PrintCurrentSaveData() {
	std::cout << "Current SaveData data:\n";
	std::cout << saveData.scriptPath << "\n" << saveData.scriptLine << "\n" << saveData.backgroundPath << std::endl;
	for (auto s : saveData.sprites) {
		std::cout << s.spriteName << " " << s.spriteLocation << " \n";
	}
}