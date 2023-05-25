#include "Room.hpp"

Room::Room() {
	gameStage = GS_STARTING;
}

Room::~Room() {
	for (auto player : team1) {
		delete player;
	}
	for (auto player : team2) {
		delete player;
	}
}

void Room::update(float deltaTime) {
	gameStage = GS_RUNNING;

	if (gameStage == GS_RUNNING) {
		for (auto player : team1) { player->update(deltaTime); }
		for (auto player : team2) { player->update(deltaTime); }
	}
	// we are taking snapshot at every update but actually update rate should be more
	takeSnapshot();
}

void Room::addPlayer(Player* player) {
	// here we match players 
	// we simply add one by one for now
	if (team1.size() < team2.size()) team1.push_back(player);
	else team2.push_back(player);
}

void Room::inputUpdatePlayer(uint32_t id, const void* inputData) {
	PlayerInput data{};
	memcpy(&data, inputData, sizeof(PlayerInput));

	for (auto player : team1) {
		if (player->ID == id) {
			player->inputUpdate(data);
			return;
		}
	}

	for (auto player : team2) {
		if (player->ID == id) {
			player->inputUpdate(data);
			return;
		}
	}
}

BufferInfo Room::getSnapshot(uint32_t id) {
	return snapshotBuffer.getBufferInfo();
}

sf::Vector2i Room::numOfPlayersInTeams() {
	return sf::Vector2i(team1.size(), team2.size());
}

void Room::takeSnapshot() {
	// clean the buffer
	snapshotBuffer.cleanBuffer();

	

	{
		GameStageData data;
		data.stage = GS_RUNNING;

		snapshotBuffer.writeToBuffer(&data, sizeof(GameStageData));
	}
	if (gameStage == GS_RUNNING) {
		//LOG(team1.size(), " ", team2.size());

		for (auto player : team1) {
			PlayerUpdateData data;
			//data.group = G_PLAYER;
			data.ID = player->ID;
			data.position = player->position;
			data.rotation = player->rotation;
			data.turrentRotation = player->turrentRotation;
			snapshotBuffer.writeToBuffer(&data, sizeof(PlayerUpdateData));
		}

		for (auto player : team2) {
			PlayerUpdateData data;
			//data.group = G_PLAYER;
			data.ID = player->ID;
			data.position = player->position;
			data.rotation = player->rotation;
			data.turrentRotation = player->turrentRotation;
			snapshotBuffer.writeToBuffer(&data, sizeof(PlayerUpdateData));
		}
	}
}