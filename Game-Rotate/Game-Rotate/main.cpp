#include "Game.h"
#include "vector2.h"
#include <iostream>

int main(int argc, char** argv) {

	Game* game = new Game();

	bool success = game->Initialize();
	if (success) {
		game->MainLoop();
	}
	game->Shutdown();
	return 0;
}
