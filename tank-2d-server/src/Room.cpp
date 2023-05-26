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

void Room::inputUpdatePlayer(uint32_t id, void* inputData, size_t size) {
	Buffer inputBuffer;
	inputBuffer.writeToBuffer(inputData, size);

	int header;
	inputBuffer.startReading();

	while (!inputBuffer.autoReadIsDone()) {
		inputBuffer.autoReadHeader(&header);
		// we must handle all type of data
		if (header == H_PLAYER_USERNAME) {
			PlayerUsername data;
			inputBuffer.autoReadFromBuffer(&data, sizeof(PlayerUsername));

			updatePlayerUsername(id, data);
		}
		else if (header == H_PLAYER_INPUT) {
			PlayerInput data;
			inputBuffer.autoReadFromBuffer(&data, sizeof(PlayerInput));

			updatePlayerInput(id, data);
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
			data.team = T_FIRST;
			data.ID = player->ID;
			data.position = player->position;
			data.rotation = player->rotation;
			data.turrentRotation = player->turrentRotation;
			snapshotBuffer.writeToBuffer(&data, sizeof(PlayerUpdateData));
		}

		for (auto player : team2) {
			PlayerUpdateData data;
			data.team = T_SECOND;
			data.ID = player->ID;
			data.position = player->position;
			data.rotation = player->rotation;
			data.turrentRotation = player->turrentRotation;
			snapshotBuffer.writeToBuffer(&data, sizeof(PlayerUpdateData));
		}
	}
}

void Room::updatePlayerUsername(uint32_t id, PlayerUsername& username) {
	for (auto player : team1) {
		if (player->ID == id) {
			player->username = username.username;
			return;
		}
	}
	for (auto player : team2) {
		if (player->ID == id) {
			player->username = username.username;
			return;
		}
	}
}

void Room::updatePlayerInput(uint32_t id, PlayerInput& input) {
	for (auto player : team1) {
		if (player->ID == id) {
			player->inputUpdate(input);
			return;
		}
	}
	for (auto player : team2) {
		if (player->ID == id) {
			player->inputUpdate(input);
			return;
		}
	}
}
