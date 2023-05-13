#pragma once

#include <SFML/Graphics.hpp>

#include "constants.hpp"

class Tank {
public:
	enum Group {
		PLAYER = 0,
		ALLIE = 1,
		ENAMY = 2
	};

	Tank(uint8_t group);
	~Tank();

	void update(float deltaTime); 
	void render(sf::RenderWindow& target);
	//void onEvent(const sf::Event& event);

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const;


private:
	uint8_t group;
	const float maxSpeed;
	const float acceleration;
	const float rotationSpeed;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::ConvexShape body;
	sf::CircleShape turrent;
	sf::RectangleShape gun;
};