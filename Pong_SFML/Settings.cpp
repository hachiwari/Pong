#include "Settings.h"

Settings::Settings(RenderWindow &Window)
{
	if (!_Font.loadFromFile("pack/Font.TTF"))
	{
		cout << "Error - no files (pack/Font.TTF)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Settings# - Font loaded" << endl;
#endif

	this->_Window = &Window;
	this->_cDefaultColorBall = Color::Green;
	this->_cDefaultColorBackground = Color::Black;
	this->_cPaddle1 = Color::Cyan;
	this->_cPaddle2 = Color::Yellow;
	this->_bDefaultSound = true;
}

Settings::~Settings()
{
}

void Settings::initSettings()
{
	bool escapeToMenu = false;

	string option[6] = { "Colour", "Sound", "Background", "ON", "OFF", "<Escape to exit>" };

	Text textColour(option[0], _Font, 40);
	textColour.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textColour.getGlobalBounds().width / 2.0), 50);

	Text textSound(option[1], _Font, 40);
	textSound.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textSound.getGlobalBounds().width / 2.0), 200);

	Text textBackground(option[2], _Font, 40);
	textBackground.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textBackground.getGlobalBounds().width / 2.0), 350);

	Text textOn(option[3], _Font, 40);
	textOn.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textOn.getGlobalBounds().width / 2.0), 270);

	Text textOff(option[4], _Font, 40);
	textOff.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textOff.getGlobalBounds().width / 2.0), 270);

	Text textEscapeToMenu(option[5], _Font, 20);
	textEscapeToMenu.setPosition(static_cast<float>(_Window->getSize().x / 2.0 - textEscapeToMenu.getGlobalBounds().width / 2.0), 500);

	for (int i = 0; i < RECTANGLE_COLOR_BALL_MAX; i++)
	{
		_RectangleColorBall[i].setSize(Vector2f(60, 20));
		_RectangleColorBall[i].setPosition(static_cast<float>(270 + 100 * i), 120);
	}

	_RectangleColorBall[0].setFillColor(Color::Red);
	_RectangleColorBall[1].setFillColor(Color::Green);
	_RectangleColorBall[2].setFillColor(Color::Blue);

	for (int i = 0; i < RECTANGLE_COLOR_BACKGROUND_MAX; i++)
	{
		_RectangleColorBackground[i].setSize(Vector2f(60, 20));
		_RectangleColorBackground[i].setPosition(static_cast<float>(270 + 100 * i), 420);
	}

	_RectangleColorBackground[0].setFillColor(Color::Red);
	_RectangleColorBackground[1].setFillColor(Color::Black);
	_RectangleColorBackground[2].setFillColor(Color::Green);

	while (escapeToMenu != true)
	{
		Vector2f vMouse(Mouse::getPosition(*_Window));
		Event eEvent;

		while (_Window->pollEvent(eEvent))
		{
			if (eEvent.type == Event::KeyReleased && eEvent.key.code == Keyboard::Escape)
				escapeToMenu = true;
		}

		if (_RectangleColorBall[0].getGlobalBounds().contains(vMouse) && eEvent.type == Event::MouseButtonPressed)
		{
			_cDefaultColorBall = Color::Red;
		}
		else if (_RectangleColorBall[0].getGlobalBounds().contains(vMouse) == false && eEvent.type == Event::MouseButtonPressed)
		{
			_RectangleColorBall[0].setOutlineThickness(0);
			_RectangleColorBall[0].setFillColor(Color::Red);
		}

		if (_RectangleColorBall[1].getGlobalBounds().contains(vMouse) && eEvent.type == Event::MouseButtonPressed)
		{
			_cDefaultColorBall = Color::Green;
		}
		else if (_RectangleColorBall[1].getGlobalBounds().contains(vMouse) == false && eEvent.type == Event::MouseButtonPressed)
		{
			_RectangleColorBall[1].setOutlineThickness(0);
			_RectangleColorBall[1].setFillColor(Color::Green);
		}

		if (_RectangleColorBall[2].getGlobalBounds().contains(vMouse) && eEvent.type == Event::MouseButtonPressed)
		{
			_cDefaultColorBall = Color::Blue;
		}
		else if (_RectangleColorBall[2].getGlobalBounds().contains(vMouse) == false && eEvent.type == Event::MouseButtonPressed)
		{
			_RectangleColorBall[2].setOutlineThickness(0);
			_RectangleColorBall[2].setFillColor(Color::Blue);
		}

		// Sound
		if (textOn.getGlobalBounds().contains(vMouse) && eEvent.type == Event::MouseButtonPressed && eEvent.key.code == Mouse::Left)
		{
			_bDefaultSound = (_bDefaultSound) ? false : true;
		}

		// Background
		if (_RectangleColorBackground[0].getGlobalBounds().contains(vMouse) && eEvent.type == Event::MouseButtonPressed)
		{
			_cDefaultColorBackground = Color::Red;
		}
		else if (_RectangleColorBackground[0].getGlobalBounds().contains(vMouse) == false && eEvent.type == Event::MouseButtonPressed)
		{
			_RectangleColorBackground[0].setOutlineThickness(0);
			_RectangleColorBackground[0].setFillColor(Color::Red);
		}

		if (_RectangleColorBackground[1].getGlobalBounds().contains(vMouse) && eEvent.type == Event::MouseButtonPressed)
		{
			_cDefaultColorBackground = Color::Black;
		}
		else if (_RectangleColorBackground[1].getGlobalBounds().contains(vMouse) == false && eEvent.type == Event::MouseButtonPressed)
		{
			_RectangleColorBackground[1].setOutlineThickness(0);
			_RectangleColorBackground[1].setFillColor(Color::Black);
		}

		if (_RectangleColorBackground[2].getGlobalBounds().contains(vMouse) && eEvent.type == Event::MouseButtonPressed)
		{
			_cDefaultColorBackground = Color::Green;
		}
		else if (_RectangleColorBackground[2].getGlobalBounds().contains(vMouse) == false && eEvent.type == Event::MouseButtonPressed)
		{
			_RectangleColorBackground[2].setOutlineThickness(0);
			_RectangleColorBackground[2].setFillColor(Color::Green);
		}

		// Zaznaczenie wybranych opcji //

		// ColorBall
		if (_cDefaultColorBall == Color::Red)
		{
			_RectangleColorBall[0].setOutlineThickness(5);
			_RectangleColorBall[0].setOutlineColor(Color::White);
		}
		else if (_cDefaultColorBall == Color::Green)
		{
			_RectangleColorBall[1].setOutlineThickness(5);
			_RectangleColorBall[1].setOutlineColor(Color::White);
		}
		else if (_cDefaultColorBall == Color::Blue)
		{
			_RectangleColorBall[2].setOutlineThickness(5);
			_RectangleColorBall[2].setOutlineColor(Color::White);
		}

		// ColroBackground
		if (_cDefaultColorBackground == Color::Red)
		{
			_RectangleColorBackground[0].setOutlineThickness(5);
			_RectangleColorBackground[0].setOutlineColor(Color::White);
		}
		else if (_cDefaultColorBackground == Color::Black)
		{
			_RectangleColorBackground[1].setOutlineThickness(5);
			_RectangleColorBackground[1].setOutlineColor(Color::White);
		}
		else if (_cDefaultColorBackground == Color::Green)
		{
			_RectangleColorBackground[2].setOutlineThickness(5);
			_RectangleColorBackground[2].setOutlineColor(Color::White);
		}

		_Window->clear(Color::Black);
		_Window->draw(textColour);
		_Window->draw(textSound);
		_Window->draw(textBackground);
		_Window->draw(textEscapeToMenu);

		if (_bDefaultSound)
			_Window->draw(textOn);
		else
			_Window->draw(textOff);

		for (int i = 0; i < RECTANGLE_COLOR_BALL_MAX; i++)
			_Window->draw(_RectangleColorBall[i]);
		for (int i = 0; i < RECTANGLE_COLOR_BACKGROUND_MAX; i++)
			_Window->draw(_RectangleColorBackground[i]);

		_Window->display();
	}
}

Color Settings::getDefaultColorBall()
{
	return this->_cDefaultColorBall;
}

Color Settings::getDefaultColorBackground()
{
	return this->_cDefaultColorBackground;
}

Color Settings::getDeafultColorPaddle(playerList player)
{
	return (player == P1) ? this->_cPaddle1 : this->_cPaddle2;
}

bool Settings::isSound()
{
	return this->_bDefaultSound;
}
