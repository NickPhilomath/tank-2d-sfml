#pragma once

#include <vector>
#include <thread>

#include "Entity.hpp"
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
	std::vector<Entity*> entities;
	Server server;
};