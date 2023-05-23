#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

#include "clientConstants.hpp"



class Tank {
public:

	Tank(Group group, TankProps props, int id);
	~Tank();

	void update(float deltaTime, sf::Vector2i mousePos);
	void render(sf::RenderWindow& target);
	//void onEvent(const sf::Event& event);

	void setPosition(sf::Vector2f pos);
	void setRotation(float r);
	void setTurrentRotation(float r);
	sf::Vector2f getPosition() const;
	float getRotation() const;
	float getTurrentRotation() const;

	float speed;

	PlayerInput input{};
	PlayerInput* getInput();

	int ID;

private:
	const TankProps props;
	const Group group;
	
	AccelerationStage acceleration_stage;

	sf::ConvexShape body;
	sf::CircleShape turrent;
	sf::RectangleShape gun;

};