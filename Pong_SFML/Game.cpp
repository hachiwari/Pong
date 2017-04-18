#include "Game.h"

RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

Game::Game() : _Settings(new Settings(window)), _Engine(new Engine(window, *_Settings))
{
	if (!_Font.loadFromFile("pack/Font.TTF"))
	{
		cout << "Error - no files (pack/Font.TTF)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Game# - Font loaded" << endl;
#endif

	if (!_Music.openFromFile("pack/Audio/music.ogg"))
	{
		cout << "Error - no files (pack/Audio/music.ogg)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Game# - Music loaded" << endl;
#endif

	if (!_BackgroundTexture.loadFromFile("pack/MenuBackground.png"))
	{
		cout << "Error - no files (pack/MenuBackground.png)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Game# - BackgroundTexture loaded" << endl;
#endif

	_Background.setTexture(_BackgroundTexture);
	this->_Window = &window;
	this->_State = MENU;
	this->_TypeGame = CHOOSE;
}

Game::~Game()
{
	delete _Settings;
	delete _Engine;
}

void Game::initGame()
{
	while (_State != QUIT)
	{
		switch (_State)
		{
			case MENU:
			{	
				menuGame();
				break;
			}

			case CHOICE:
			{
				menuTypeGame();
				break;
			}

			case GAME:
			{
				if (_TypeGame != CHOOSE)
				{
					_Music.stop();
					_Engine->initEngine(_TypeGame);
					_TypeGame = CHOOSE;
					_State = CHOICE;
				}
				break;
			}

			case SETTINGS:
			{
				_Music.stop();
				_Settings->initSettings();
				_State = MENU;
				break;
			}
		}
	}
}

void Game::menuGame()
{
	if (_Settings->isSound())
		_Music.play();

	string option[3] = { "Play", "Settings", "Quit" };

	Text textPlay(option[0], _Font, 40);
	textPlay.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textPlay.getGlobalBounds().width / 2.0), 280);

	Text textSettings(option[1], _Font, 40);
	textSettings.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textSettings.getGlobalBounds().width / 2.0), 380);

	Text textQuit(option[2], _Font, 40);
	textQuit.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textQuit.getGlobalBounds().width / 2.0), 480);

	while (_State == MENU)
	{
		Vector2f vMouse(Mouse::getPosition(*_Window)); // pobranie pozycji myszki w okienku
		Event eEvent;

		while (_Window->pollEvent(eEvent))
		{
			if (eEvent.type == sf::Event::KeyReleased && eEvent.key.code == sf::Keyboard::Escape)
				_State = QUIT;
			else if (eEvent.type == Event::Closed || textQuit.getGlobalBounds().contains(vMouse) && eEvent.type == sf::Event::MouseButtonPressed && eEvent.key.code == sf::Mouse::Left)
				_State = QUIT;
			else if (textPlay.getGlobalBounds().contains(vMouse) && eEvent.type == sf::Event::MouseButtonPressed && eEvent.key.code == sf::Mouse::Left)
				_State = CHOICE;
			else if (textSettings.getGlobalBounds().contains(vMouse) && eEvent.type == sf::Event::MouseButtonPressed && eEvent.key.code == sf::Mouse::Left)
				_State = SETTINGS;
		}

		textPlay.setFillColor((textPlay.getGlobalBounds().contains(vMouse)) ? Color::Red : Color::White);
		textSettings.setFillColor((textSettings.getGlobalBounds().contains(vMouse)) ? Color::Red : Color::White);
		textQuit.setFillColor((textQuit.getGlobalBounds().contains(vMouse)) ? Color::Red : Color::White);

		_Window->clear(Color::Black);
		_Window->draw(_Background);

		_Window->draw(textPlay);
		_Window->draw(textSettings);
		_Window->draw(textQuit);

		_Window->display();
	}
}

void Game::menuTypeGame()
{
	string option[TYPE_GAME_MAX] = { "PVC", "PVP" };

	Text textTypePVC(option[0], _Font, 40);
	textTypePVC.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textTypePVC.getGlobalBounds().width / 2.0), 280);

	Text textTypePVP(option[1], _Font, 40);
	textTypePVP.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textTypePVP.getGlobalBounds().width / 2.0), 380);

	while (_State == CHOICE)
	{
		Vector2f vMouse(Mouse::getPosition(*_Window));
		Event eEvent;

		while (_Window->pollEvent(eEvent))
		{
			if (eEvent.type == sf::Event::KeyReleased && eEvent.key.code == sf::Keyboard::Escape)
			{
				_State = MENU;
			}
			else if (textTypePVC.getGlobalBounds().contains(vMouse) && eEvent.type == sf::Event::MouseButtonPressed && eEvent.key.code == sf::Mouse::Left)
			{
				_TypeGame = PVC;
				_State = GAME;
			}
			else if (textTypePVP.getGlobalBounds().contains(vMouse) && eEvent.type == sf::Event::MouseButtonPressed && eEvent.key.code == sf::Mouse::Left)
			{
				_TypeGame = PVP;
				_State = GAME;
			}
		}

		textTypePVC.setFillColor((textTypePVC.getGlobalBounds().contains(vMouse)) ? Color::Red : Color::White);
		textTypePVP.setFillColor((textTypePVP.getGlobalBounds().contains(vMouse)) ? Color::Red : Color::White);

		_Window->clear(Color::Black);
		_Window->draw(_Background);
		_Window->draw(textTypePVC);
		_Window->draw(textTypePVP);
		_Window->display();
	}
}
