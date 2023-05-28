#pragma once

#include "constants.hpp" // we are including this from server project

constexpr auto VIEW_WIDTH = 1000; //1280
constexpr auto VIEW_HEIGHT = 800;
constexpr auto APP_TITLE = "Tank 2d";

// ratio between texture lenght in pixels and actual length in meters
constexpr float RATIO = 938 / TANK_ABRAMS().length;

struct TankAbramsInfo {
	const int body_length = 938;    // pixels
	const int body_width = 456;     // pixels
	const int turrent_length = 1030;// pixels
	const int turrent_width = 450;  // pixels
};

constexpr int GROUND_L = 1000;
constexpr int GROUND_W = 1000;

enum GameFlag {
	ON_MAIN_MENU = 0,
	ON_CONNECT,
	CONNECTION_FAIL,
	IN_GAME,
};