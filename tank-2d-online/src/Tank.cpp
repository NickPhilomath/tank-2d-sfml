#include "Tank.hpp"

Tank::Tank(Team team, int id) :
    ID{id},
    team{team}
{
    acceleration_stage = A_NO_POWER;
    speed = 0.f;
    position = sf::Vector2f(0, 0);
    rotation = 0.f;
    turrentRotation = 0.f;

    if (!t_body.loadFromFile("assets/body.png")) {
        throw std::runtime_error("cannot load asset");
    }

    if (!t_turrent.loadFromFile("assets/turrent.png")) {
        throw std::runtime_error("cannot load asset");
    }

    body.setTexture(&t_body);
    body.setTextureRect(sf::IntRect(0, 0, tankInfo.body_length, tankInfo.body_width));
    body.setSize(sf::Vector2f(tankInfo.body_length, tankInfo.body_width));
    body.setOrigin(sf::Vector2f(tankInfo.body_length / 2, tankInfo.body_width / 2));

    turrent.setTexture(&t_turrent);
    turrent.setTextureRect(sf::IntRect(0, 0, tankInfo.turrent_length, tankInfo.turrent_width));
    turrent.setSize(sf::Vector2f(tankInfo.turrent_length, tankInfo.turrent_width));
    turrent.setOrigin(sf::Vector2f(tankInfo.body_length / 2 - 180, tankInfo.body_width / 2));
}

Tank::~Tank() {
}

void Tank::update(float deltaTime, sf::Vector2i mousePos) {
    // for the f*cking server
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        inputServer.move = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        inputServer.move = -1;
    else
        inputServer.move = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        inputServer.rotate = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        inputServer.rotate = -1;
    else
        inputServer.rotate = 0;

    float angle = atan2(VIEW_HEIGHT / 2.f - mousePos.y, VIEW_WIDTH / 2.f - mousePos.x) * RAD2DEG + 180.f;
    inputServer.tRotate = angle;
    //// ****
    switch (acceleration_stage)
    {
    case A_NO_POWER:
        if (speed > 0) speed -= deltaTime * GROUND_FRICTION_ACCELERATION;
        else if (speed < 0) speed += deltaTime * GROUND_FRICTION_ACCELERATION;
        break;
    case A_FORWARD:
        speed += deltaTime * tankProps.acceleration;
        break;
    case A_BACKWARD:
        speed -= deltaTime * tankProps.acceleration;
        break;
    case A_BREAKE:
        if (speed < 0) speed -= deltaTime * tankProps.break_acceleration;
        else if (speed > 0) speed += deltaTime * tankProps.break_acceleration;
        break;
    default:
        break;
    }

    if (speed > tankProps.forward_maxSpeed) speed = tankProps.forward_maxSpeed;
    else if (speed < tankProps.backward_maxSpeed) speed = tankProps.backward_maxSpeed;

    sf::Vector2f velocity;
    velocity.x = speed * cos(rotation * DEG2RAD);
    velocity.y = speed * sin(rotation * DEG2RAD);
    position = sf::Vector2f(position.x + velocity.x * deltaTime, position.y + velocity.y * deltaTime);

    if (input.rotate != 0) {
        float deltaRotate = input.rotate * tankProps.rotationSpeed * deltaTime;
        if (input.move == -1) deltaRotate *= -1; // rotate reverse if player pressed back
        rotation += deltaRotate;
        turrentRotation += deltaRotate; // if body rotates turrent rotates as well
    }
    //input.turrentRotate = (angle > gun.getRotation()) == abs(gun.getRotation() - angle) > 180 ? -1 : 1;
    /*
    // mouse movement 
    float gunAngle = gun.getRotation();
    float angle = atan2(VIEW_HEIGHT / 2.f - mousePos.y, VIEW_WIDTH / 2.f - mousePos.x) * RAD2DEG + 180.f;
    int gunRotateSign = (angle > gunAngle) == abs(gunAngle - angle) > 180 ? -1 : 1;
    //std::cout << gun.getRotation() << std::endl;
    gun.setRotation(gunAngle + gunRotateSign * props.turrentRotationSpeed * deltaTime);
    */

    body.setPosition(position * RATIO);
    body.setRotation(rotation);
    turrent.setPosition(position * RATIO);
    turrent.setRotation(turrentRotation);
}

void Tank::render(sf::RenderWindow& target) {
    target.draw(body);
    target.draw(turrent);
}

//void Tank::onEvent(const sf::Event& event) {
//}

PlayerInput* Tank::getInput() {
    return &inputServer;
}
