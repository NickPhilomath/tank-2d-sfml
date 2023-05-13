#pragma once

constexpr auto VIEW_WIDTH = 1280;
constexpr auto VIEW_HEIGHT = 800;
constexpr auto APP_TITLE = "Tank 2d";
constexpr auto DEG2RAD = 3.14159f / 180.0f;
constexpr auto GROUND_FRICTION_ACCELERATION = 50.f;

enum Group {
	G_PLAYER = 0,
	G_ALLIE = 1,
	G_ENAMY = 2
};
enum AccelerationState {
	A_NO_POWER = 0,
	A_FORWARD = 1,
	A_BACKWARD = 2,
	A_BREAKE = 3
};