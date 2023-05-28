#include "Camera.hpp"

Camera::Camera(uint32_t viewWidth, uint32_t viewHeight) :
	rotateSpeed{30.f}
{
	cameraView.setSize(viewWidth, viewHeight);
	cameraView.zoom(1.8f);
	lastMousePos = sf::Mouse::getPosition();
}

Camera::~Camera() {
}

void Camera::onEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseWheelMoved)
	{
		cameraView.zoom(1.f - event.mouseWheel.delta * .1f);
	}
}

void Camera::update(float deltaTime) {
	//cameraView.setRotation(cameraView.getRotation() - deltaMove.x * rotateSpeed * deltaTime);
	cameraView.setCenter(viewTarget->position * RATIO);
}
