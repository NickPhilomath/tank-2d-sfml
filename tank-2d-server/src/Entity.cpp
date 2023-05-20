#include "Entity.hpp"

Entity::Entity(ENetPeer* peer, uint32_t id) :
	peer{ peer }, ID{id} {
    acceleration_stage = A_NO_POWER;
    speed = 0.f;
}

Entity::~Entity() {
}

void Entity::update(float deltaTime) {
    
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
        speed += deltaTime * props.break_acceleration;
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

    if (input.turrentRotate != 0) {
        float deltaRotate = input.turrentRotate * props.turrentRotationSpeed * deltaTime;
        turrentRotation += deltaRotate;
    }
}

void Entity::inputUpdate(PlayerInput input) {
    if (input.move == 1) {
        acceleration_stage = A_FORWARD;
    }
    if (input.move == -1) {
        acceleration_stage = A_BACKWARD;
    }
    if (input.move == 0) {
        acceleration_stage = A_NO_POWER;
    }
    this->input = input;
}
