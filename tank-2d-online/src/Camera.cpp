#include "Camera.hpp"

#ifdef _DEBUG
	#include <iostream>
#endif // _DEBUG


Camera::Camera(uint32_t viewWidth, uint32_t viewHeight) {
	cameraView.setSize(viewWidth, viewHeight);
	lastMousePos = sf::Mouse::getPosition();
}

Camera::~Camera() {
}

void Camera::update(float deltaTime) {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2i deltaMove = lastMousePos - mousePos;
	lastMousePos = mousePos;

	cameraView.setCenter(viewTarget->getPosition());
}
