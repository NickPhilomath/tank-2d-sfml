#pragma once 

#include <enet/enet.h>
#include <SFML/System.hpp>

class Player {
public:
	Player(ENetPeer* peer);
	~Player();

	ENetPeer* peer;
	uint32_t ID;
	float speed;
	float rotation;
	float turrentRotation;
	sf::Vector2f position;
private:

};