#pragma once 

#include <enet/enet.h>
#include <SFML/System.hpp>

#include "constants.hpp"

class Player {
public:
	Player(ENetPeer* peer, uint32_t id);
	~Player();

	void update(float deltaTime);
	void inputUpdate(PlayerInput input);

	const ENetPeer* peer;
	const uint32_t ID;
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