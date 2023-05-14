#pragma once

#include <thread>
#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "Tank.hpp"
#include "Camera.hpp"
#include "Client.hpp"

class Game {
public:
	Game();
	~Game();

	void run();

private:
	void createWindow();
	void networkFunction();

	sf::RenderWindow window; 
	Tank* playerTank;
	std::vector<Tank*> tanks;
	Client client;
};