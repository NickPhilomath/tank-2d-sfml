#include "Player.hpp"

Player::Player(ENetPeer* peer, uint32_t id) :
	peer{ peer }, ID{id} {
    acceleration_stage = A_NO_POWER;
    speed = 0.f;
}

Player::~Player() {
}

void Player::update(float deltaTime) {
    LOG(acceleration_stage);

    switch (acceleration_stage)
    {
    case A_NO_POWER:
        if (speed > 0) speed -= deltaTime * GROUND_FRICTION_ACCELERATION;
        else if (speed < 0) speed += deltaTime * GROUND_FRICTION_ACCELERATION;
        break;
    case A_FORWARD:
        speed += deltaTime * props.acceleration;
        break;
    case A_BACKWARD:
        speed -= deltaTime * props.acceleration;
        break;
    case A_BREAKE:
        if (speed < 0) speed -= deltaTime * props.break_acceleration;
        else if (speed > 0) speed += deltaTime * props.break_acceleration;
        break;
    default:
        break;
    }

    if (speed > props.forward_maxSpeed) speed = props.forward_maxSpeed;
    if (speed < props.backward_maxSpeed) speed = props.backward_maxSpeed;

    sf::Vector2f velocity;
    velocity.x = speed * cos(rotation * DEG2RAD);
    velocity.y = speed * sin(rotation * DEG2RAD);
    position = sf::Vector2f(position.x + velocity.x * deltaTime, position.y + velocity.y * deltaTime);

    if (input.rotate != 0) {
        float deltaRotate = input.rotate * props.rotationSpeed * deltaTime;
        if (input.move == -1) deltaRotate *= -1; // rotate reverse if player pressed back
        rotation += deltaRotate;
        turrentRotation += deltaRotate; // if body rotates turrent rotates as well
    }

    // turrent
    turrentRotation = input.turrentRotation;
        //float deltaRotate = input.turrentRotate * props.turrentRotationSpeed * deltaTime;
        //turrentRotation += deltaRotate;
}

void Player::inputUpdate(PlayerInput input) {
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
    this->input = input;
}
