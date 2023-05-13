#include "Tank.hpp"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


Tank::Tank(Group group) :
    forward_maxSpeed{ 100.f },
    backward_maxSpeed{ 70.f },
    forward_acceleration{ 200.f },
    backward_acceleration{ 150.f },
    break_acceleration{ 500.f },
    rotationSpeed{ 40.f },
    group{ group }
{
    acceleration_state = A_NO_POWER;
    rotation = 0.f;
    speed = 0.f;
    // creating shape 
    body.setPointCount(4);
    body.setPoint(0, sf::Vector2f(30.f, 20.f));
    body.setPoint(1, sf::Vector2f(30.f, -20.f));
    body.setPoint(2, sf::Vector2f(-30.f, -20.f));
    body.setPoint(3, sf::Vector2f(-30.f, 20.f));
    body.setFillColor(sf::Color(0, 0, 0, 0));
    body.setOutlineThickness(2);
    turrent.setRadius(15.f);
    turrent.setOutlineThickness(2);
    turrent.setFillColor(sf::Color(0, 0, 0, 0));
    turrent.setOrigin(15, 15);
    gun.setSize(sf::Vector2f(50, 4));
    gun.setOrigin(sf::Vector2f(-13, 2));

    if (group == G_ALLIE) {
        body.setOutlineColor(sf::Color::Green);
        turrent.setOutlineColor(sf::Color::Green);
        gun.setFillColor(sf::Color::Green);
    }
    else if (group == G_ENAMY) {
        body.setOutlineColor(sf::Color::Red);
        turrent.setOutlineColor(sf::Color::Red);
        gun.setFillColor(sf::Color::Red);
    }
    else {
        body.setOutlineColor(sf::Color::White);
        turrent.setOutlineColor(sf::Color::White);
        gun.setFillColor(sf::Color::White);
    }

}

Tank::~Tank() {
}

void Tank::update(float deltaTime) {
    int move = 0, rotate = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotate = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotate = -1;

    if (move == 1) {
        acceleration_state = speed < 0 ? A_BREAKE : A_FORWARD;
    }
    if (move == -1) {
        acceleration_state = speed > 0 ? A_BREAKE : A_BACKWARD;
    }
    if (move == 0) {
        acceleration_state = A_NO_POWER;
    }

    switch (acceleration_state)
    {
    case A_NO_POWER:
        if (speed > 0) speed -= deltaTime * GROUND_FRICTION_ACCELERATION;
        if (speed < 0) speed += deltaTime * GROUND_FRICTION_ACCELERATION;
        break;
    case A_FORWARD:
        speed += deltaTime * forward_acceleration;
        break;
    case A_BACKWARD:
        speed -= deltaTime * backward_acceleration;
        break;
    case A_BREAKE:
        speed += deltaTime * break_acceleration * move;
        break;
    default:
        break;
    }

    sf::Vector2f velocity;
    velocity.x = speed * cos(rotation * DEG2RAD);
    velocity.y = speed * sin(rotation * DEG2RAD);
    setPosition(sf::Vector2f(position.x + velocity.x * deltaTime, position.y + velocity.y * deltaTime));

    if (rotate != 0) setRotation(rotation + rotate * rotationSpeed * deltaTime);
}

void Tank::render(sf::RenderWindow& target) {
    target.draw(body);
    target.draw(turrent);
    target.draw(gun);
}

//void Tank::onEvent(const sf::Event& event) {
//}

void Tank::setPosition(sf::Vector2f pos) {
    position = pos;
    body.setPosition(pos);
    turrent.setPosition(pos);
    gun.setPosition(pos);
}

void Tank::setRotation(float r) {
    rotation = r;
    body.setRotation(r);
}

sf::Vector2f Tank::getPosition() const {
    return position;
}
