#pragma once

#include "constants.hpp" // we are including this from server project

constexpr auto VIEW_WIDTH = 1000; //1280
constexpr auto VIEW_HEIGHT = 800;
constexpr auto APP_TITLE = "Tank 2d";

struct TankAbramsInfo {
	const int body_lenght = 938;    // pixels
	const int body_width = 456;     // pixels
	const int turrent_lenght = 1030;// pixels
	const int turrent_width = 450;  // pixels
	const TANK_ABRAMS props = TANK_ABRAMS(); // server properties
};

// ratio between texture lenght in pixels and actual length in meters
constexpr float RATIO = TankAbramsInfo().body_lenght / TANK_ABRAMS().length;

enum GameFlag {
	ON_MAIN_MENU = 0,
	ON_CONNECT,
	CONNECTION_FAIL,
	IN_GAME,
};