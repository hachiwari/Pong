#include "Engine.h"

Engine::Engine(RenderWindow &Window, Settings &Settings) : _Ball(new Ball(Window, Settings, BALL_RADIUS)), _Paddle1(new Paddle(Window, Settings, Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), Settings.getDeafultColorPaddle(P1))), _Paddle2(new Paddle(Window, Settings, Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT), Settings.getDeafultColorPaddle(P2)))
{
	if (!_Font.loadFromFile("pack/Font.TTF"))
	{
		cout << "Error - no files (pack/Font.TTF)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Engine# - Font loaded" << endl;
#endif

	if (!_BackgroundTexture.loadFromFile("pack/GameBackground.png"))
	{
		cout << "Error - no files (pack/GameBackground.png)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Engine# - BackgroundTexture loaded" << endl;
#endif

	if (!_SoundScoreBuffer.loadFromFile("pack/Audio/score.wav"))
	{
		cout << "Error - no files (pack/Audio/score.wav)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Engine# - Audio loaded" << endl;
#endif

	_Background.setTexture(_BackgroundTexture);
	_SoundScore.setBuffer(_SoundScoreBuffer);

	this->_Window = &Window;
	this->_Settings = &Settings;
}

Engine::~Engine()
{
	delete _Ball;
	delete _Paddle1;
	delete _Paddle2;
}

void Engine::initEngine(typeGame TypeGame)
{
	resetGame();

	float currentTime = 0.0f;
	float previousTime = 0.0f;
	float deltaTime = 0.0f;
	bool escapeToMenu = false;
	bool ballMoving = false;
	bool ballStopped = true;
	int ballRandomDirection = -1;

	Event eEvent;
	Clock Clock;
	RectangleShape topRect;
	RectangleShape bottomRect;
	RectangleShape leftRect;
	RectangleShape rightRect;
	Text textTitle("Score", _Font, 40);
	Text textScoreP1(to_string(getScorePlayer(P1)), _Font, 40);
	Text textScoreP2(to_string(getScorePlayer(P2)), _Font, 40);
	Text textWin("", _Font, 70);
	Text textEscape("PREES ESCAPE TO GO TO MENU", _Font, 20);

	topRect.setSize(Vector2f(TOP_RECT_WIDTH, TOP_RECT_HEIGHT));
	bottomRect.setSize(Vector2f(BOTTOM_RECT_WIDTH, BOTTOM_RECT_HEIGHT));
	leftRect.setSize(Vector2f(LEFT_RECT_WIDTH, LEFT_RECT_HEIGHT));
	rightRect.setSize(Vector2f(RIGHT_RECT_WIDTH, RIGHT_RECT_HEIGHT));

	topRect.setFillColor(_cBackground);
	bottomRect.setFillColor(_cBackground);
	leftRect.setFillColor(_cBackground);
	rightRect.setFillColor(_cBackground);

	topRect.setPosition(Vector2f(0, 0));
	bottomRect.setPosition(Vector2f(0, WINDOW_HEIGHT - BOTTOM_RECT_HEIGHT));
	leftRect.setPosition(Vector2f(0, 0));
	rightRect.setPosition(Vector2f(WINDOW_WIDTH - RIGHT_RECT_WIDTH, 0));

	textTitle.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textTitle.getGlobalBounds().width / 2.0), 15);
	textScoreP1.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textScoreP1.getGlobalBounds().width / 2.0 - 150.0), 40);
	textScoreP2.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textScoreP2.getGlobalBounds().width / 2.0 + 150.0), 40);
	textEscape.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textEscape.getGlobalBounds().width / 2.0), 340.0f);

	while (escapeToMenu != 1)
	{
		if (_Winner == -1)
		{
			currentTime = Clock.getElapsedTime().asSeconds();
			deltaTime = currentTime - previousTime;
			previousTime = currentTime;

			while (_Window->pollEvent(eEvent))
			{
				if (eEvent.type == Event::KeyReleased && eEvent.key.code == Keyboard::Escape)
					escapeToMenu = true;
			}

			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				_Paddle1->move(deltaTime, UP);
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				_Paddle1->move(deltaTime, DOWN);
			}

			if (TypeGame == PVC)
			{
				if (_Ball->getPosition().y < _Paddle2->getPosition().y)
					_Paddle2->move(deltaTime/* / 1.5*/, UP);

				if (_Ball->getPosition().y + 2 * _Ball->getRadius() >
					_Paddle2->getPosition().y + _Paddle2->getSize().y)
					_Paddle2->move(deltaTime/* / 1.5*/, DOWN);
			}
			else if (TypeGame == PVP)
			{
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					_Paddle2->move(deltaTime, UP);
				}

				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					_Paddle2->move(deltaTime, DOWN);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (!ballMoving && ballStopped)
				{
					ballMoving = true;
					ballStopped = false;
				}
			}

			// Kolizje
			if (_Paddle1->isCollision(topRect))
			{
				_Paddle1->setPosition(Vector2f(_Paddle1->getPosition().x, TOP_RECT_HEIGHT));
			}

			if (_Paddle1->isCollision(bottomRect))
			{
				_Paddle1->setPosition(Vector2f(_Paddle1->getPosition().x, WINDOW_HEIGHT - BOTTOM_RECT_HEIGHT - PADDLE_HEIGHT));
			}

			if (_Paddle2->isCollision(topRect))
			{
				_Paddle2->setPosition(Vector2f(_Paddle2->getPosition().x, TOP_RECT_HEIGHT));
			}

			if (_Paddle2->isCollision(bottomRect))
			{
				_Paddle2->setPosition(Vector2f(_Paddle2->getPosition().x, WINDOW_HEIGHT - BOTTOM_RECT_HEIGHT - PADDLE_HEIGHT));
			}

			if (_Ball->isCollision(_Paddle1->getRect()) /* && _Ball->getPosition().x <= 65*/)
			{
				if (_Settings->isSound())
				{
					_Ball->playHitSound();
				}

				_Ball->reflection(X);
				_Ball->acceleration(*_Paddle1);
			}

			if (_Ball->isCollision(_Paddle2->getRect()) /* && _Ball->getPosition().x >= 735*/)
			{
				if (_Settings->isSound())
				{
					_Ball->playHitSound();
				}

				_Ball->reflection(X);
				_Ball->acceleration(*_Paddle2);
			}

			if (_Ball->isCollision(topRect))
			{
				_Ball->reflection(Y);
			}

			if (_Ball->isCollision(bottomRect))
			{
				_Ball->reflection(Y);
			}

			if (_Ball->isCollision(leftRect))
			{
				if (_Settings->isSound())
				{
					_SoundScore.play();
				}

				setScorePlayer(P2, 1);
				textScoreP2.setString(to_string(getScorePlayer(P2)));

				_Ball->initBall(getDefaultPositionBall());
				_Paddle1->initPaddle(Vector2f(60.0f, 270.0f));
				ballMoving = false;
				ballStopped = true;
				_Ball->resetSpeed(ballRandomDirection * (-1));
			}

			if (_Ball->isCollision(rightRect))
			{
				if (_Settings->isSound())
				{
					_SoundScore.play();
				}

				setScorePlayer(P1, 1);
				textScoreP1.setString(to_string(getScorePlayer(P1)));

				_Ball->initBall(getDefaultPositionBall());
				_Paddle2->initPaddle(Vector2f(730.0f, 270.0f));
				ballMoving = false;
				ballStopped = true;
				_Ball->resetSpeed(ballRandomDirection * (-1));
			}

			// Punktacja
			if (getScorePlayer(P1) >= SCORE_MAX && (getScorePlayer(P1) - getScorePlayer(P2) >= DELTA_SCORE))
			{
				resetGame();
				textScoreP1.setString("0");
				textScoreP2.setString("0");
				ballMoving = false;
				ballStopped = true;
				_Winner = P1;
			}
			else if (getScorePlayer(P2) >= SCORE_MAX && ((getScorePlayer(P2) - getScorePlayer(P1)) >= DELTA_SCORE))
			{

				resetGame();
				textScoreP1.setString("0");
				textScoreP2.setString("0");
				ballMoving = false;
				ballStopped = true;
				_Winner = P2;
			}

			if (ballMoving && !ballStopped)
				_Ball->move();

			_Window->clear(_cBackground);
			_Window->draw(_Background);
			_Window->draw(topRect);
			_Window->draw(bottomRect);
			_Window->draw(leftRect);
			_Window->draw(rightRect);

			_Window->draw(textTitle);
			_Window->draw(textScoreP1);
			_Window->draw(textScoreP2);

			_Ball->draw();
			_Paddle1->draw();
			_Paddle2->draw();
			_Window->display();
		}
		else
		{
			while (_Window->pollEvent(eEvent))
			{
				if (eEvent.type == Event::KeyReleased && eEvent.key.code == Keyboard::Escape)
					escapeToMenu = true;
			}

			string text = (_Winner == P1) ? "PLAYER 1 WIN" : "PLAYER 2 WIN";
			textWin.setString(text);
			textWin.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textWin.getGlobalBounds().width / 2.0), 215.0f);

			_Window->clear(_cBackground);
			_Window->draw(textWin);
			_Window->draw(textEscape);
			_Window->display();
		}
	}
}

int Engine::getScorePlayer(int idPlayer)
{
	if (idPlayer >= PLAYER_MAX)
	{
		cout << "Engine# - unkown player" << endl;
		exit(0);
	}

	return _iScorePlayer[idPlayer];
}

void Engine::setScorePlayer(int idPlayer, int iScore)
{
	int currentScore = getScorePlayer(idPlayer);

	_iScorePlayer[idPlayer] = currentScore + iScore;
}

void Engine::resetGame()
{
	this->_cBall = _Settings->getDefaultColorBall();
	this->_cBackground = _Settings->getDefaultColorBackground();

	for (int i = 0; i < PLAYER_MAX; i++)
		this->_iScorePlayer[i] = 0;

	_Ball->initBall(getDefaultPositionBall());
	_Paddle1->initPaddle(Vector2f(60.0f, 270.0f));
	_Paddle2->initPaddle(Vector2f(730.0f, 270.0f));
	_Winner = -1;
}

Vector2f Engine::getDefaultPositionBall()
{
	Vector2f DEFAULT_POSITION = Vector2f(WINDOW_WIDTH / 2.0f - BALL_RADIUS, 320.0f);

	return DEFAULT_POSITION;
}
