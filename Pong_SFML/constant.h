#pragma once
#include <iostream>

#define RECTANGLE_COLOR_BALL_MAX 3
#define RECTANGLE_COLOR_BACKGROUND_MAX 3
#define PLAYER_MAX 2
#define SCORE_MAX 10
#define DELTA_SCORE 2

#define TYPE_GAME_MAX 2

enum stateGame {
	MENU,
	CHOICE,
	GAME,
	SETTINGS,
	QUIT
};

enum typeGame {
	CHOOSE,
	PVC,	// Player vs Computer
	PVP		// Player vs Player
};

enum playerList {
	P1,
	P2
};

enum controlPaddle {
	UP,
	DOWN,
};

enum axis {
	X,
	Y
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string WINDOW_NAME = "Pong_SFML";

const float TOP_RECT_WIDTH = WINDOW_WIDTH;
const float TOP_RECT_HEIGHT = 100.0f;
const float BOTTOM_RECT_WIDTH = WINDOW_WIDTH;
const float BOTTOM_RECT_HEIGHT = 50.0f;
const float LEFT_RECT_WIDTH = 50.0f;
const float LEFT_RECT_HEIGHT = WINDOW_HEIGHT;
const float RIGHT_RECT_WIDTH = 50.0f;
const float RIGHT_RECT_HEIGHT = WINDOW_HEIGHT;

const float BALL_RADIUS = 10.0f;

const float PADDLE_WIDTH = 10.0f;
const float PADDLE_HEIGHT = 100.0f;
const float PADDLE_SPEED = 450.0f;
