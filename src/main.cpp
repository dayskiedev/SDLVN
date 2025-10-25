#include <iostream>
#include "Game.h"

int main(int argc, char* args[]) {
	Game game;
	if (!game.Init()) {
		std::cout << "Failed to launch project! Exiting..." << std::endl;
		return -1;
	}

	while (game.running) {
		game.Run();
	}

	game.Quit();

	return 0;
}
