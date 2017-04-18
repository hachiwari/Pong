#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "constant.h"
#include "Settings.h"
#include "Engine.h"

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();

	void initGame();
	void menuGame();
	void menuTypeGame();

private:
	Settings* _Settings;
	Engine* _Engine;

	RenderWindow* _Window;
	Font _Font;
	Music _Music;
	Texture _BackgroundTexture;
	Sprite _Background;
	stateGame _State;
	typeGame _TypeGame;
};
