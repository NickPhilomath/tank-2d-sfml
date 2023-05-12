#pragma once

#include <SFML/Graphics.hpp>

#include "constants.hpp"

class Tank {
public:
	Tank();
	~Tank();

	void update(float deltaTime); 
	void render(sf::RenderWindow& target);
	//void onEvent(const sf::Event& event);

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition() const;

private:
	const float maxSpeed;
	const float acceleration;
	const float rotationSpeed;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::ConvexShape body;
};