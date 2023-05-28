#pragma once 

#include <vector>
#include "Player.hpp"
#include "Buffer.hpp"

class Room {
public:

	Room();
	~Room();

	void update(float deltaTime);

	void addPlayer(ServerPlayer* player);
	void inputUpdatePlayer(uint32_t id, void* inputData, size_t size);
	BufferInfo getSnapshot(uint32_t id);
	sf::Vector2i numOfPlayersInTeams();

private:
	void takeSnapshot();
	void updatePlayerUsername(uint32_t id, PlayerUsername& username);
	void updatePlayerInput(uint32_t id, PlayerInput& input);

	std::vector<ServerPlayer*> team1;
	std::vector<ServerPlayer*> team2;

	GameStage gameStage;
	Buffer snapshotBuffer;
};