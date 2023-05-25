#pragma once 

#include <vector>
#include "Player.hpp"
#include "Buffer.hpp"

class Room {
public:

	Room();
	~Room();

	void update(float deltaTime);

	void addPlayer(Player* player);
	void inputUpdatePlayer(uint32_t id, const void* inputData);
	BufferInfo getSnapshot(uint32_t id);
	sf::Vector2i numOfPlayersInTeams();

private:
	void takeSnapshot();

	std::vector<Player*> team1;
	std::vector<Player*> team2;

	GameStage gameStage;
	Buffer snapshotBuffer;
};