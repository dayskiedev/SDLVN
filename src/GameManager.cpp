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

	saveManager = std::make_unique<SaveManager>();

	//
	//SCREEN_WIDTH = 1920;
	//SCREEN_HEIGHT = 1080;
	//SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	//SDL_SetWindowFullscreen(gWindow, true);
	//SDL_SetWindowBordered(gWindow, SDL_FALSE);
	
	// checking for memory leaks
	//for (int i = 0; i < 599; ++i) {
	//	ChangeState(std::make_unique<Load>());
	//	ChangeState(std::make_unique<Menu>());
	//}

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

}   

void GameManager::ChangeState(std::unique_ptr<GameState> state) {
	if (currentState) {
		currentState->ExitState();
		currentState.reset();
	}
		
	currentState = std::move(state);
	currentState->EnterState(gRenderer, this);
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

void GameManager::SaveGame(Interpreter& interpreterInfo, std::shared_ptr<SpriteManager> spriteManagerInfo, std::shared_ptr<Sprite> background) {
	
	// grab details from interpretor about current game state
	// which can then be sent through the save manager to be
	// formatted and saved into binary format!

	// this will need to be updated with save path

	// interpretor has function (get gamestate data??)
	// returns current line, current background reiiruferuire
	// pass that through here to game save?

	SaveManager::SaveData rawGameData;

	rawGameData.scriptPath = interpreterInfo.GetCurrentScript();
	rawGameData.scriptLine = interpreterInfo.GetCurrentScriptLine();

	rawGameData.backgroundPath = background->GetSpriteTexPath();

	std::vector<SpriteInformation> spriteInfoRaw;
	for (auto s : spriteManagerInfo->GetSprites()) {
		SpriteInformation sInfo;

		sInfo.spriteName = s->GetSpriteName();
		sInfo.spriteLocation = s->GetSpriteTexPath();
		sInfo.w = s->getWidth();
		sInfo.h = s->getHeight();
		sInfo.x = s->getX();
		sInfo.y = s->getY();
		
		spriteInfoRaw.push_back(sInfo);
	}

	rawGameData.sprites = spriteInfoRaw;

	saveManager->Save(rawGameData);
}

void GameManager::LoadSave(std::string savePath) {
	// this will set the GameManagers saveStruct which will be used by the interpretor

	if (!saveManager->Load(saveData, savePath)) {
		std::cout << "error loading save";
	}
}