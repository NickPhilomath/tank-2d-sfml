#pragma once

#include <thread>
#include <SFML/Graphics.hpp>

#include "clientConstants.hpp"
#include "Tank.hpp"
#include "Camera.hpp"
#include "Client.hpp"
#include "UI.hpp"

class Game {
public:
	Game();
	~Game();

	void run();

private:
	void createWindow();
	void networkFunction();

	void snapshotUpdate();

	sf::ConvexShape mapBorder;
	Tank* playerTank;
	std::vector<Tank*> tanks;

	UI ui;
	Client client;
	sf::Clock clock;
	sf::RenderWindow window;
	Camera camera{ VIEW_WIDTH, VIEW_HEIGHT };
	GameFlag gameFlag;
	bool connectionFail = false;
	
	TransferBuffer snapShot;
};