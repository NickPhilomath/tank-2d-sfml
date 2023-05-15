#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <stdexcept>
#include <enet/enet.h>

#include "App.hpp"

int main() {
	App app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}