#include <iostream>
#include "Game.h"
#include "GameManager.h"

int main(int argc, char* args[]) {
	Game game;
	GameManager gameManager;
	
	if (!gameManager.Init()) {
		std::cout << "Failed to launch project! Exiting..." << std::endl;
		return -1;
	}

	std::cout << "Initiated startup, attempting to run" << std::endl;

	while (gameManager.running) {
		gameManager.Run();
	}

	gameManager.Quit();

	return 0;
}
