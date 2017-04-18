#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "constant.h"

using namespace sf;
using namespace std;

class Settings
{
public:
	Settings(RenderWindow &Window);
	~Settings();

	void initSettings();
	Color getDefaultColorBall();
	Color getDefaultColorBackground();
	Color getDeafultColorPaddle(playerList player);
	bool isSound();

private:
	RenderWindow *_Window;
	Font _Font;
	RectangleShape _RectangleColorBall[RECTANGLE_COLOR_BALL_MAX];
	RectangleShape _RectangleColorBackground[RECTANGLE_COLOR_BACKGROUND_MAX];
	Color _cDefaultColorBall;
	Color _cDefaultColorBackground;
	Color _cPaddle1;
	Color _cPaddle2;

	bool _bDefaultSound;
};

