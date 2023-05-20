#pragma once 

#include <enet/enet.h>
#include <SFML/System.hpp>

#include "constants.hpp"

class Entity {
public:
	Entity(ENetPeer* peer, uint32_t id);
	~Entity();

	void update(float deltaTime);
	void inputUpdate(PlayerInput input);

	const ENetPeer* peer;
	const uint32_t ID;
	const TankProps props{};

	float speed;
	float rotation;
	float turrentRotation;
	sf::Vector2f position;
	AccelerationStage acceleration_stage;

	PlayerInput input{};

private:

};