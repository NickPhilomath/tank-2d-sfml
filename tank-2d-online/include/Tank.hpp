#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

#include "clientConstants.hpp"



class Tank {
public:

	Tank(Team team, int id);
	~Tank();

	void update(float deltaTime, sf::Vector2i mousePos);
	void render(sf::RenderWindow& target);
	//void onEvent(const sf::Event& event);

	float speed;
	float rotation;
	float turrentRotation;
	sf::Vector2f position;
	AccelerationStage acceleration_stage;

	PlayerInput input{};
	PlayerInput inputServer{};
	PlayerInput* getInput();

	int ID;

private:
	Team team;
	const TankAbramsInfo tankInfo{};
	const TANK_ABRAMS tankProps{};

	sf::Texture t_body;
	sf::Texture t_turrent;
	sf::RectangleShape body;
	sf::RectangleShape turrent;
};