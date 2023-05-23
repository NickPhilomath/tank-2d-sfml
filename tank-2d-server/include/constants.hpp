#pragma once 

#include <SFML/System.hpp>

constexpr auto DEG2RAD = 3.14159f / 180.0f;
constexpr auto RAD2DEG = 180.0f / 3.14159f;
constexpr auto GROUND_FRICTION_ACCELERATION = 50.f;

enum Group {
	G_PLAYER = 0,
	G_ALLIE,
	G_ENAMY
};

enum DataHeader {
	H_PLAYER_UPDATE = 0,
	H_ADD_PLAYER,
	H_BULLET_UPDATE,
	H_ADD_BULLET
};

struct SnapshotInfo {
	const void* snapshotData;
	size_t size;
};

struct TransferData {
	DataHeader header;
	Group group;
	uint32_t ID;
	sf::Vector2f position;
	float speed;
	float rotation;
	float turrentRotation;
};

struct TankProps {
	float forward_maxSpeed = 200.f;
	float backward_maxSpeed = -70.f;
	float forward_acceleration = 120.f;
	float backward_acceleration = 70.f;
	float break_acceleration = -400.f;
	float rotationSpeed = 60.f;
	float turrentRotationSpeed = 90.f;
};

struct PlayerInput {
	int move;
	int rotate;
	int turrentRotate;
};

enum AccelerationStage {
	A_NO_POWER = 0,
	A_FORWARD,
	A_BACKWARD,
	A_BREAKE
};

// utilities

#ifdef _DEBUG
#include <iostream>

template<typename ...T>
void Print(T&&... args) {
	(std::cout << ... << args);
}

#define LOG(...) Print(__VA_ARGS__, '\n')

#else

#define LOG(...)

#endif