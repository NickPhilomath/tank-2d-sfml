#pragma once 

#include <vector>
#include "Player.hpp"

class Room {
public:

	Room();
	~Room();

	void update(float deltaTime);

	void addPlayer(Player* player);
	void inputUpdatePlayer(uint32_t id, const void* inputData);
	SnapshotInfo getSnapshot(uint32_t id);
	sf::Vector2i numOfPlayersInTeams();

private:
	void takeSnapshot();
	void changeGroupNameByPlayerPOV(uint32_t id);

	std::vector<Player*> team1;
	std::vector<Player*> team2;

	std::vector<TransferData> snapshot; // <- here it is
};