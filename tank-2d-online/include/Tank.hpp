#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

#include "constants.hpp"

struct TankProps
{
	float forward_maxSpeed = 200.f;
	float backward_maxSpeed = -70.f;
	float forward_acceleration = 120.f;
	float backward_acceleration = 90.f;
	float break_acceleration = 400.f;
	float rotationSpeed = 60.f;
	float turrentRotationSpeed = 90.f;
};

class Tank {
public:

	Tank(Group group, TankProps props);
	~Tank();

	void update(float deltaTime, sf::Vector2i mousePos);
	void render(sf::RenderWindow& target);
	//void onEvent(const sf::Event& event);

	void setPosition(sf::Vector2f pos);
	void setRotation(float r);
	void setTurrentRotation(float r);
	sf::Vector2f getPosition() const;


private:
	const TankProps props;
	const Group group;
	
	float speed;
	AccelerationStage acceleration_stage;

	sf::ConvexShape body;
	sf::CircleShape turrent;
	sf::RectangleShape gun;
};