#pragma once 

#include <SFML/Graphics.hpp>

#include "Tank.hpp"

class Camera {
public:
	Camera(uint32_t viewWidth, uint32_t viewHeight);
	~Camera();

	void update(float deltaTime);

	sf::View cameraView;
	Tank* viewTarget;

private:
	sf::Vector2i lastMousePos;
};