#include <iostream>
#include "GameManager.h"

int main(int argc, char* args[]) {
	GameManager gameManager;
	
	if (!gameManager.Init()) { 
		std::cout << "Failed to launch project! Exiting..." << std::endl;
		return -1;
	}

	while (gameManager.running) {
		gameManager.Run();
	}

	gameManager.Quit();
	std::cout << "Quit!\n";

	return 0;
}
