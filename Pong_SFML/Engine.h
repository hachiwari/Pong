#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "constant.h"
#include "Settings.h"
#include "Ball.h"

#include <string>
#include <sstream>

using namespace sf;
using namespace std;

class Engine
{
public:
	Engine(RenderWindow &Window, Settings &Settings);
	~Engine();

	void initEngine(typeGame TypeGame);
	int getScorePlayer(int idPlayer);
	void setScorePlayer(int idPlayer, int iScore);
	void resetGame();
	void initRectangleShape();
	Vector2f getDefaultPositionBall();

private:
	RenderWindow *_Window;
	Settings* _Settings;
	Ball* _Ball;
	Paddle* _Paddle1;
	Paddle* _Paddle2;

	Font _Font;
	Color _cBall;
	Color _cBackground;
	Music _Music;
	Texture _BackgroundTexture;
	Sprite _Background;
	SoundBuffer _SoundScoreBuffer;
	Sound _SoundScore;

	short _iScorePlayer[PLAYER_MAX];
	short _Winner;
};

