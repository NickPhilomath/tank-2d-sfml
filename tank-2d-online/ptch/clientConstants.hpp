#pragma once

#include "constants.hpp" // we are including this from server project

constexpr auto VIEW_WIDTH = 1000; //1280
constexpr auto VIEW_HEIGHT = 800;
constexpr auto APP_TITLE = "Tank 2d";

enum GameFlag {
	ON_MAIN_MENU = 0,
	ON_CONNECT,
	CONNECTION_FAIL,
	IN_GAME,
};