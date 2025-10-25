#include <iostream>
#include "Game.h"

#include "SaveManager.h"

int main(int argc, char* args[]) {
	Game game;
	if (!game.Init()) {
		std::cout << "Failed to launch project! Exiting..." << std::endl;
		return -1;
	}

	SaveManager s;
	s.Save();

	while (game.running) {
		game.Run();
	}

	game.Quit();

	return 0;
}
