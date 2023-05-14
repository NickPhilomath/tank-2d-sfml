#pragma once 

#include <SFML/Graphics.hpp>

#include "Tank.hpp"

class Camera {
public:
	Camera(uint32_t viewWidth, uint32_t viewHeight);
	~Camera();

	void onEvent(const sf::Event& event);
	void update(float deltaTime);

	sf::View cameraView;
	Tank* viewTarget;

private:
	const float rotateSpeed;
	sf::Vector2i lastMousePos;
};