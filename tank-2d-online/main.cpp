#include <iostream>
#include <stdexcept>
#include "Game.hpp"

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