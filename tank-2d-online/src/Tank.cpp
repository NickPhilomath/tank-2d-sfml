#include "Tank.hpp"

Tank::Tank() : 
	acceleration{10.f}, maxSpeed{100.f}, rotationSpeed{40.f} {
    // creating shape 
    body.setPointCount(4);
    body.setPoint(0, sf::Vector2f(20.f, 30.f));
    body.setPoint(1, sf::Vector2f(20.f, -30.f));
    body.setPoint(2, sf::Vector2f(-20.f, -30.f));
    body.setPoint(3, sf::Vector2f(-20.f, 30.f));

    body.setFillColor(sf::Color(0, 0, 0, 0));
    body.setOutlineColor(sf::Color::White);
    body.setOutlineThickness(2);
    body.setPosition(0.0f, 0.0f);
}

Tank::~Tank() {
}

void Tank::update(float deltaTime) {
    int move = 0, rotate = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        rotate = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        rotate = -1;

    setPosition(sf::Vector2f(position.x + rotate, position.y + move));
}

void Tank::render(sf::RenderWindow& target) {
    target.draw(body);
}

//void Tank::onEvent(const sf::Event& event) {
//}

void Tank::setPosition(sf::Vector2f pos) {
    position = pos;
    body.setPosition(pos);
}

sf::Vector2f Tank::getPosition() const {
    return position;
}
