#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "constant.h"
#include "Settings.h"
#include "Paddle.h"

using namespace sf;
using namespace std;

class Ball
{
public:
	Ball(RenderWindow &Window, Settings &Settings, float Radius);
	~Ball();

	void initBall(Vector2f Position);
	void draw();
	void move();
	bool isCollision(RectangleShape Rectangle);
	bool isCollision(FloatRect Rect);
	void reflection(axis axis);
	void playHitSound();
	void acceleration(Paddle Paddle);
	void resetSpeed(int sign);
	Vector2f getPosition();
	float getRadius();

private:
	RenderWindow *_Window;
	Settings* _Settings;
	CircleShape _BallObject;

	Color _Color;
	SoundBuffer _PaddleHit;
	Sound _SoundPaddleHit;
	Vector2f _vCurrentSpeed;

	float _fRadius;
};
