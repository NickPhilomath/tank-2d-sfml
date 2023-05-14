#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <stdexcept>

#include "Game.hpp"
#include "Client.hpp"

int main() {
	Game game;

	try {
		game.run();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}