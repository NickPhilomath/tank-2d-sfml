#include "Tank.hpp"

constexpr int body_width = 938, body_height = 456;
constexpr int turrent_width = 1030, turrent_height = 450;

Tank::Tank(TankProps props, int team, int id) :
    props{ props },
    ID{id},
    team{team}
{
    acceleration_stage = A_NO_POWER;
    speed = 0.f;

    if (!t_body.loadFromFile("assets/body.png")) {
        throw std::runtime_error("cannot load asset");
    }

    if (!t_turrent.loadFromFile("assets/turrent.png")) {
        throw std::runtime_error("cannot load asset");
    }

    body.setTexture(&t_body);
    body.setTextureRect(sf::IntRect(0, 0, body_width, body_height));
    body.setSize(sf::Vector2f(body_width, body_height));
    body.scale(sf::Vector2f(0.2, 0.2));
    body.setOrigin(sf::Vector2f(body_width / 2, body_height / 2));

    turrent.setTexture(&t_turrent);
    turrent.setTextureRect(sf::IntRect(0, 0, turrent_width, turrent_height));
    turrent.setSize(sf::Vector2f(turrent_width, turrent_height));
    turrent.scale(sf::Vector2f(0.2, 0.2));
    turrent.setOrigin(sf::Vector2f(body_width / 2 - 180, body_height / 2));
}

Tank::~Tank() {
}

void Tank::update(float deltaTime, sf::Vector2i mousePos) {
    input.move = 0;
    input.rotate = 0;
    input.turrentRotation = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        input.move = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        input.move = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        input.rotate = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        input.rotate = -1;

    float angle = atan2(VIEW_HEIGHT / 2.f - mousePos.y, VIEW_WIDTH / 2.f - mousePos.x) * RAD2DEG + 180.f;
    input.turrentRotation = angle;
    //input.turrentRotate = (angle > gun.getRotation()) == abs(gun.getRotation() - angle) > 180 ? -1 : 1;
    /*
    // if player suddenly changes movement tank uses break first
    if (input.move == 1) {
        acceleration_stage = speed < 0 ? A_BREAKE : A_FORWARD;
    }
    if (input.move == -1) {
        acceleration_stage = speed > 0 ? A_BREAKE : A_BACKWARD;
    }
    if (input.move == 0) {
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
        speed += deltaTime * props.break_acceleration * input.move;
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
    float deltaRotate = input.rotate * rotateSign * props.rotationSpeed * deltaTime;
    if (input.rotate != 0) {
        setRotation(body.getRotation() + deltaRotate);
        setTurrentRotation(gun.getRotation() + deltaRotate);
    }

    // mouse movement 
    float gunAngle = gun.getRotation();
    float angle = atan2(VIEW_HEIGHT / 2.f - mousePos.y, VIEW_WIDTH / 2.f - mousePos.x) * RAD2DEG + 180.f;
    int gunRotateSign = (angle > gunAngle) == abs(gunAngle - angle) > 180 ? -1 : 1;
    //std::cout << gun.getRotation() << std::endl;
    gun.setRotation(gunAngle + gunRotateSign * props.turrentRotationSpeed * deltaTime);
    */
}

void Tank::render(sf::RenderWindow& target) {
    target.draw(body);
    target.draw(turrent);
}

//void Tank::onEvent(const sf::Event& event) {
//}

void Tank::setPosition(sf::Vector2f pos) {
    body.setPosition(pos);
    turrent.setPosition(pos);
}

void Tank::setRotation(float r) {
    body.setRotation(r);
}

void Tank::setTurrentRotation(float r)
{
    turrent.setRotation(r);
}

sf::Vector2f Tank::getPosition() const {
    return body.getPosition();
}

float Tank::getRotation() const {
    return body.getRotation();
}

float Tank::getTurrentRotation() const {
    return turrent.getRotation();
}

PlayerInput* Tank::getInput() {
    return &input;
}
