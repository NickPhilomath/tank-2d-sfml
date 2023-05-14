#include "Tank.hpp"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


Tank::Tank(Group group, TankProps props) :
    props{ props },
    group{ group }
{
    acceleration_stage = A_NO_POWER;
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

void Tank::update(float deltaTime, sf::Vector2i mousePos) {
    int move = 0, rotate = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotate = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotate = -1;

    // if player suddenly changes movement tank uses break first
    if (move == 1) {
        acceleration_stage = speed < 0 ? A_BREAKE : A_FORWARD;
    }
    if (move == -1) {
        acceleration_stage = speed > 0 ? A_BREAKE : A_BACKWARD;
    }
    if (move == 0) {
        acceleration_stage = A_NO_POWER;
    }

    switch (acceleration_stage)
    {
    case A_NO_POWER:
        if (speed > 0) speed -= deltaTime * GROUND_FRICTION_ACCELERATION;
        if (speed < 0) speed += deltaTime * GROUND_FRICTION_ACCELERATION;
        break;
    case A_FORWARD:
        speed += deltaTime * props.forward_acceleration;
        break;
    case A_BACKWARD:
        speed -= deltaTime * props.backward_acceleration;
        break;
    case A_BREAKE:
        speed += deltaTime * props.break_acceleration * move;
        break;
    default:
        break;
    }

    if (speed > props.forward_maxSpeed) speed = props.forward_maxSpeed;
    if (speed < props.backward_maxSpeed) speed = props.backward_maxSpeed;

    sf::Vector2f velocity;
    velocity.x = speed * cos(body.getRotation() * DEG2RAD);
    velocity.y = speed * sin(body.getRotation() * DEG2RAD);
    setPosition(sf::Vector2f(getPosition().x + velocity.x * deltaTime, getPosition().y + velocity.y * deltaTime));

    int rotateSign = speed >= 0 ? 1 : -1; // rotate reverse if tank is moving backward
    float deltaRotate = rotate * rotateSign * props.rotationSpeed * deltaTime;
    if (rotate != 0) {
        setRotation(body.getRotation() + deltaRotate);
        setTurrentRotation(gun.getRotation() + deltaRotate);
    }

    // mouse movement 
    float gunAngle = gun.getRotation();
    float angle = atan2(VIEW_HEIGHT / 2.f - mousePos.y, VIEW_WIDTH / 2.f - mousePos.x) * RAD2DEG + 180.f;
    int gunRotateSign = (angle > gunAngle) == abs(gunAngle - angle) > 180 ? -1 : 1;
    //std::cout << gun.getRotation() << std::endl;
    gun.setRotation(gunAngle + gunRotateSign * props.turrentRotationSpeed * deltaTime);

}

void Tank::render(sf::RenderWindow& target) {
    target.draw(body);
    target.draw(turrent);
    target.draw(gun);
}

//void Tank::onEvent(const sf::Event& event) {
//}

void Tank::setPosition(sf::Vector2f pos) {
    body.setPosition(pos);
    turrent.setPosition(pos);
    gun.setPosition(pos);
}

void Tank::setRotation(float r) {
    body.setRotation(r);
}

void Tank::setTurrentRotation(float r)
{
    gun.setRotation(r);
}

sf::Vector2f Tank::getPosition() const {
    return body.getPosition();
}
