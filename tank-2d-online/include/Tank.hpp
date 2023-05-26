#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

#include "clientConstants.hpp"



class Tank {
public:

	Tank(int team, int id);
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
	const TankAbramsInfo tankInfo = TankAbramsInfo();
	int team;

	AccelerationStage acceleration_stage;

	sf::Texture t_body;
	sf::Texture t_turrent;
	sf::RectangleShape body;
	sf::RectangleShape turrent;
};