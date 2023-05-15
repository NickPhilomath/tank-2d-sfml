#pragma once 

#include <SFML/System.hpp>

enum Group {
	G_PLAYER = 0,
	G_ALLIE = 1,
	G_ENAMY = 2
};

struct TransferBuffer {
	Group group;
	sf::Vector2f position;
	float speed;
	float rotation;
	float turrentRotation;
};