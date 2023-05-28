#pragma once 

#include <SFML/System.hpp>

constexpr auto DEG2RAD = 3.14159f / 180.0f;
constexpr auto RAD2DEG = 180.0f / 3.14159f;
constexpr auto GROUND_FRICTION_ACCELERATION = 0.5f;

constexpr auto NET_UPDATE = 50; // milliseconds   (usually 50)

constexpr auto MAP_LENGTH = 500; // meters
constexpr auto MAP_WIDTH = 500;  // meters

struct TANK_ABRAMS {
	const float length = 7.4f;				// meters
	const float width = 3.6f;				// meters
	const float mass = 54000.f;				// kg
	const float power = 1500.f;				// horse power
	const float forward_maxSpeed = 11.f;    // m/s   (40 km/h)
	const float backward_maxSpeed = -5.f;   // m/s   (18 km/h)
	const float acceleration = 2.f;		    // m/s2    
	const float break_acceleration = -10.f; // m/s2
	const float rotationSpeed = 60.f;       // grad/s
	const float turrentRotationSpeed = 90.f;// grad/s
};

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

// from client
struct PlayerInput {
	DataHeader header = H_PLAYER_INPUT;
	int move = 0;
	int rotate = 0;
	float tRotate = 0.f;
};

struct PlayerUsername {
	DataHeader header = H_PLAYER_USERNAME;
	char username[32];
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
	AccelerationStage accelerationStage;

	PlayerInput playerInput;
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