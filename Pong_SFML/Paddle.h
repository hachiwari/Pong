#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "constant.h"
#include "Settings.h"

using namespace sf;
using namespace std;

class Paddle
{
public:
	Paddle(RenderWindow &Window, Settings &Settings, Vector2f Size, Color Color);
	~Paddle();

	void initPaddle(Vector2f Position);
	void draw();
	void move(float deltaTime, controlPaddle control);
	bool isCollision(RectangleShape Rectangle);
	void setPosition(Vector2f Position);
	Vector2f getPosition();
	FloatRect getRect();
	Vector2f getSize();

private:
	RenderWindow *_Window;
	Settings* _Settings;

	RectangleShape _PaddleObject;
};
