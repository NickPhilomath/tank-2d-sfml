#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

#include "constants.hpp"

class Tank {
public:

	Tank(Group group);
	~Tank();

	void update(float deltaTime); 
	void render(sf::RenderWindow& target);
	//void onEvent(const sf::Event& event);

	void setPosition(sf::Vector2f pos);
	void setRotation(float r);
	sf::Vector2f getPosition() const;


private:
	const float forward_maxSpeed;
	const float backward_maxSpeed;
	const float forward_acceleration;
	const float backward_acceleration;
	const float break_acceleration;
	const float rotationSpeed;
	const Group group;
	
	float speed;
	float rotation;
	float turrentRotation;
	sf::Vector2f position;
	AccelerationState acceleration_state;

	sf::ConvexShape body;
	sf::CircleShape turrent;
	sf::RectangleShape gun;
};