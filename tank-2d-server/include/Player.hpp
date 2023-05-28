#pragma once 

#include <enet/enet.h>
#include <SFML/System.hpp>

#include "constants.hpp"

class Player {
public:
	Player();
	~Player();

	void update(float deltaTime);
	const TANK_ABRAMS props{};
	std::string username;

	float speed;
	float rotation;
	float turrentRotation;
	sf::Vector2f position;
	AccelerationStage acceleration_stage;

	PlayerInput input{};

private:

};

class ServerPlayer : public Player {
public:
	ServerPlayer(ENetPeer* peer, uint32_t id);
	void inputUpdate(PlayerInput input);

	const uint32_t ID;
	const ENetPeer* peer;
private:
};