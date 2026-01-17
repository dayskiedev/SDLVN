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
	gWindow = SDL_CreateWindow(PROGRAM_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RELATIVE_SCREEN_WIDTH, RELATIVE_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	// here is how we will handle scaling for different resolutions with a single number
	// the game ui is set around the idea we have a 1280 x 720 screen dont ask me why i just started with that ok
	// from there we can increase or decrease it by fixed amounts using a scaler
	// the math for this is easy. ex: 1920/1280 = 1.5 so to get 1080p we scale by 1.5
	// 1440p means 2560 / 1280 = 2
	SDL_RenderSetScale(gRenderer, RESOLUTION_SCALE, RESOLUTION_SCALE);
	SDL_SetWindowSize(gWindow, RELATIVE_SCREEN_WIDTH * RESOLUTION_SCALE,  RELATIVE_SCREEN_HEIGHT * RESOLUTION_SCALE);

	if (FULLSCREEN) {
		SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	// 
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

	std::cout << "Mixer initialised" << std::endl;

	audioManager.LoadSystemSounds();

	// start off by setting the launch state TO a menu instance
	currentState = std::make_unique<Menu>();
	currentState->EnterState(gRenderer, this);

	std::cout << "Default state initialised" << std::endl;

	saveManager = std::make_unique<SaveManager>();

	std::cout << "Save Manager initialised" << std::endl;

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
		sInfo.spriteScale = s->GetScale();
		sInfo.w = s->getWidth();
		sInfo.h = s->getHeight();
		sInfo.x = s->getX();
		sInfo.y = s->getY();

		spriteInfoRaw.push_back(sInfo);
	}
	saveData.sprites = spriteInfoRaw;
	saveData.musicPath = _interpreterInfo->GetCurrentMusicPath();
	saveData.musPlaying = _interpreterInfo->GetMusicPlaying();
}

void GameManager::SaveGame(std::string savePath) {
	// here we just perfrom the quick save but we want to pass it through to the save manager
	// in order to actually write the data into binary
	if (SaveExists(savePath)) {
		std::cout << "Warning overwriting save, should double check user somehow idk" << std::endl;
	}


	QuickSave();
	saveManager->Save(saveData, savePath);
}

void GameManager::LoadSave(std::string savePath) {
	// this will set the GameManagers saveStruct which will be used by the interpretor
	if (!SaveExists(savePath)) {
		std::cout << "Unable to find save: " << savePath << std::endl;
		return;
	}


	if (!saveManager->Load(saveData, savePath)) {
		std::cout << "error loading save";
		return;
	}

	RequestState(std::make_unique<Game>());
}

void GameManager::DeleteSave(std::string savePath) {
	saveManager->Delete(savePath);
}

void GameManager::DeleteAllSaves(std::string savePath) {
	saveManager->DeleteAll(savePath);
}

void GameManager::PrintCurrentSaveData() {
	std::cout << "Current SaveData data:\n";
	std::cout << saveData.scriptPath << "\n" << saveData.scriptLine << "\n" << saveData.backgroundPath << std::endl;
	for (auto s : saveData.sprites) {
		std::cout << s.spriteName << " " << s.spriteLocation << " \n";
	}
}