#pragma once

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "Tank.hpp"

class Game {
public:
	Game();
	~Game();

	void run();

private:
	void createWindow();

	sf::RenderWindow window; 
	Tank* playerTank;
	std::vector<Tank*> tanks;
};