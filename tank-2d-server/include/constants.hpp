#pragma once 

#include <SFML/System.hpp>

constexpr auto DEG2RAD = 3.14159f / 180.0f;
constexpr auto RAD2DEG = 180.0f / 3.14159f;
constexpr auto GROUND_FRICTION_ACCELERATION = 50.f;

enum AccelerationStage {
	A_NO_POWER = 0,
	A_FORWARD,
	A_BACKWARD,
	A_BREAKE
};

enum Team {
	T_FIRST = 0,
	T_SECOND,
	T_UNKNOWN
};

enum DataHeader {
	// server
	H_GAME_STAGE = 0,
	H_PLAYER_UPDATE,
	H_PLAYER_ID,
	// client
	H_PLAYER_INPUT,
	H_PLAYER_USERNAME
};

enum GameStage {
	GS_STARTING = 0,
	GS_RUNNING,
	GS_ENDED
};

// from the server
struct BufferInfo {
	void* bufferData;
	size_t size;
};

struct GameStageData {
	DataHeader header = H_GAME_STAGE;
	GameStage stage;
};

struct PlayerIDData {
	DataHeader header = H_PLAYER_ID;
	uint32_t id;
};

struct PlayerUpdateData {
	DataHeader header = H_PLAYER_UPDATE;
	Team team;
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

// from client
struct PlayerInput {
	DataHeader header = H_PLAYER_INPUT;
	int move;
	int rotate;
	float turrentRotation;
};

struct PlayerUsername {
	DataHeader header = H_PLAYER_USERNAME;
	char username[32];
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