#include "Room.hpp"

Room::Room() {
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
	for (auto player : team1) { player->update(deltaTime); }
	for (auto player : team2) { player->update(deltaTime); }

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

SnapshotInfo Room::getSnapshot(uint32_t id) {
	changeGroupNameByPlayerPOV(id); // *too long comment here*
	SnapshotInfo snapshotInfo{};
	snapshotInfo.snapshotData = static_cast<void*>(snapshot.data());
	snapshotInfo.size = snapshot.size() * sizeof(TransferData);
	return snapshotInfo;
}

sf::Vector2i Room::numOfPlayersInTeams() {
	return sf::Vector2i(team1.size(), team2.size());
}

void Room::takeSnapshot() {
	snapshot.clear();

	for (auto player : team1) {
		TransferData data;
		data.header = H_PLAYER_UPDATE;
		//data.group = G_PLAYER;
		data.ID = player->ID;
		data.position = player->position;
		data.rotation = player->rotation;
		data.turrentRotation = player->turrentRotation;

		snapshot.push_back(data);
	}

	for (auto player : team2) {
		TransferData data;
		data.header = H_PLAYER_UPDATE;
		//data.group = G_PLAYER;
		data.ID = player->ID;
		data.position = player->position;
		data.rotation = player->rotation;
		data.turrentRotation = player->turrentRotation;

		snapshot.push_back(data);
	}
}

void Room::changeGroupNameByPlayerPOV(uint32_t id) {
	bool playerIsInFirstTeam = false;
}
