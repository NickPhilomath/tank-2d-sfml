#pragma once

#include <vector>
#include <thread>

#include "Room.hpp"
#include "Player.hpp"
#include "Server.hpp"

#include "constants.hpp"

constexpr auto PORT = 1234;

class App {
public:
	App();
	~App();

	void run();

private:
	void networkFunction();

	bool running = false;
	Room room;
	Server server;
};