#pragma once

#include <thread>
#include <SFML/Graphics.hpp>

#include "clientConstants.hpp"
#include "Buffer.hpp"
#include "Tank.hpp"
#include "Camera.hpp"
#include "Client.hpp"
#include "UI.hpp"
#include "Map.hpp"

#include "Timer.hpp"

class Game {
public:
	Game();
	~Game();

	void run();

private:
	void createWindow();
	void networkFunction();

	void snapshotUpdate();
	void updatePlayer(PlayerUpdateData& data);

	Buffer snapshot;

	Map gameMap;
	Tank* playerTank;
	std::vector<Tank*> tanks;

	UI ui;
	Client client;
	Timer clock;
	sf::RenderWindow window;
	Camera camera{ VIEW_WIDTH, VIEW_HEIGHT };
	GameFlag gameFlag;
	bool connectionFail = false;
	bool windowOnFocus = true;
};