#pragma once 

#include <SFML/Graphics.hpp>

#include "clientConstants.hpp"
#include "Camera.hpp"

class Map {
public:
	Map();
	~Map();

	void update(Camera& camera);
	void render(sf::RenderWindow& window);

private:
	sf::Texture t_ground;
	std::vector<sf::RectangleShape> grounds;
	sf::RectangleShape mapBorder;

	sf::Vector2f cameraPosition;

	const int MapLength = MAP_LENGTH * RATIO;
	const int MapWidth = MAP_WIDTH * RATIO;
};